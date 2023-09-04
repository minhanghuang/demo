#include "node.h"

void Node::Init() {
  if (!ok_) return;
  std::cout << "Init." << std::endl;
}

void Node::Build() {
  if (!ok_) return;
  std::cout << "Build." << std::endl;
  uint8_t fileData[INPUT_H * INPUT_W];
  LoadInputImages();
  PrintInputImages();
  ParserModelFile();
  ParserPlanFile();
}

void Node::Inference() {
  if (!ok_) return;
  IRuntime* runtime{createInferRuntime(gLogger_)};
  engine_ = runtime->deserializeCudaEngine(engine_string_.data(),
                                           engine_string_.size());
  if (!engine_) {
    std::cout << "@@@@@@ Failed loading engine!" << std::endl;
    return;
  }
  std::cout << "@@@@@@ Succeeded building engine!" << std::endl;

  // 2. context
  // 一个引擎可以有多个执行上下文，允许将一组权重用于多个重叠的推理任务
  IExecutionContext* context = engine_->createExecutionContext();

  // 3. buffer

  // engine中输入和输出张量的总数量
  // 绑定的顺序通常是这样的：先是所有的输入绑定，然后是所有的输出绑定
  // 也就是说: 在张量的数组中, 前半部分全是输入张量的index,
  // 后半部分全是输出张量的index
  long unsigned int nIO = engine_->getNbIOTensors();
  // 输入张量的数量
  long unsigned int nInput = 0;
  // 输出张量的数量
  long unsigned int nOutput = 0;
  // 张量名
  std::vector<std::string> vTensorName(nIO);
  for (int i = 0; i < nIO; ++i) {
    vTensorName[i] = std::string(engine_->getIOTensorName(i));
    // 张量自增
    nInput += int(engine_->getTensorIOMode(vTensorName[i].c_str()) ==
                  TensorIOMode::kINPUT);
    nOutput += int(engine_->getTensorIOMode(vTensorName[i].c_str()) ==
                   TensorIOMode::kOUTPUT);
  }

  // 设置输入张量的形状: 4:张量的维度数量，{1, 1, x, y} 表示各个维度的大小。
  context->setInputShape(vTensorName[0].c_str(),
                         Dims32{4, {1, 1, INPUT_H, INPUT_W}});

  std::vector<int> vTensorSize(nIO, 0);  // 每个张量的大小
  // 遍历所有张量
  for (int i = 0; i < nIO; ++i) {
    // 获取张量形状
    Dims32 dim = context->getTensorShape(vTensorName[i].c_str());
    int size = 1;
    // 遍历张量每个维度
    for (int j = 0; j < dim.nbDims; ++j) {
      size *= dim.d[j];  // 每个维度的长度
    }
    // getTensorDataType: 获取指定张量的数据类型
    vTensorSize[i] =
        size *
        dataTypeToSize(engine_->getTensorDataType(vTensorName[i].c_str()));
  }

  // buffer
  std::vector<void*> vBufferH{nIO, nullptr};
  std::vector<void*> vBufferD{nIO, nullptr};
  // 遍历所有张量
  for (int i = 0; i < nIO; ++i) {
    // host buffer 开辟空间
    vBufferH[i] = (void*)new char[vTensorSize[i]];
    CHECK(cudaMalloc(&vBufferD[i], vTensorSize[i]));
  }

  // copy buffer host to device
  for (int i = 0; i < nInput; ++i) {
    CHECK(cudaMemcpy(vBufferD[i], vBufferH[i], vTensorSize[i],
                     cudaMemcpyHostToDevice));
  }
  for (int i = 0; i < nIO; ++i) {
    // 绑定张量的地址，即将内存缓冲区的地址与特定张量关联起来
    context->setTensorAddress(vTensorName[i].c_str(), vBufferD[i]);
  }

  // 4. execute
  // 推理
  context->enqueueV3(0);

  // copy buffer device to host
  for (int i = nInput; i < nIO; ++i) {
    CHECK(cudaMemcpy(vBufferH[i], vBufferD[i], vTensorSize[i],
                     cudaMemcpyDeviceToHost));
  }

  for (int i = 0; i < nIO; ++i) {
    printArrayInformation((float*)vBufferH[i],
                          context->getTensorShape(vTensorName[i].c_str()),
                          vTensorName[i], true);
  }

  // free buffer
  for (int i = 0; i < nIO; ++i) {
    delete[] (char*)vBufferH[i];
    CHECK(cudaFree(vBufferD[i]));
  }
  std::cout << "Inference end." << std::endl;
}

void Node::Destroy() {
  if (!ok_) return;
  ok_ = true;
}

void Node::ParserArgs(int argc, char* argv[]) {
  if (1 == argc) {
  } else if (2 == argc) {
    target_path_ = argv[1];
  } else {
    ok_ = false;
  }
}

void Node::ParserModelFile() {
  if (0 == access(plan_path_.c_str(), F_OK)) {
    return;
  }
  // 没有plan文件
  std::cout << "没有plan文件" << std::endl;
  // 1. builder
  IBuilder* builder = createInferBuilder(gLogger_);

  // 2. profile
  IOptimizationProfile* profile = builder->createOptimizationProfile();

  // 3. config
  IBuilderConfig* config = builder->createBuilderConfig();
  config->setMemoryPoolLimit(MemoryPoolType::kWORKSPACE, 1 << 30);

  // 4. network
  INetworkDefinition* network = builder->createNetworkV2(
      1U << int(NetworkDefinitionCreationFlag::kEXPLICIT_BATCH));

  // 5. parser
  nvonnxparser::IParser* parser =
      nvonnxparser::createParser(*network, gLogger_);
  if (!parser->parseFromFile(model_path_.c_str(),
                             static_cast<int>(ILogger::Severity::kINFO))) {
    std::cout << "@@@@@@@@@ parser error." << std::endl;
    return;
  }

  // 6. serialized network
  nvinfer1::IHostMemory* serialized_model =
      builder->buildSerializedNetwork(*network, *config);
  if (nullptr == serialized_model || 0 == serialized_model->size()) {
    std::cout << "Failed building serialized engine!" << std::endl;
    return;
  }

  // 7. plan
  std::ofstream new_plan_file(plan_path_, std::ios::binary);
  if (!new_plan_file) {
    std::cerr << "Failed to open .plan file for writing." << std::endl;
    return;
  }
  new_plan_file.write(static_cast<const char*>(serialized_model->data()),
                      serialized_model->size());
  new_plan_file.close();
  delete parser;
  delete network;
  delete config;
  delete builder;
}

void Node::ParserPlanFile() {
  std::ifstream plan_file(plan_path_, std::ios::binary);
  long int fsize = 0;
  plan_file.seekg(0, plan_file.end);
  fsize = plan_file.tellg();
  plan_file.seekg(0, plan_file.beg);
  engine_string_.resize(fsize);
  plan_file.read(engine_string_.data(), engine_string_.size());
}

void Node::LoadInputImages() {
  std::ifstream infile(target_path_, std::ifstream::binary);
  std::string magic, h, w, max;
  infile >> magic >> h >> w >> max;
  infile.seekg(1, infile.cur);
  infile.read(reinterpret_cast<char*>(target_buffer_), INPUT_H * INPUT_W);
  // 归一化
  for (int i = 0; i < INPUT_H * INPUT_W; i++) {
    target_buffer_[i] = target_buffer_[i] / 255;
  }
}

void Node::PrintInputImages() {
  std::cout << "\nInput:\n" << std::endl;
  for (int i = 0; i < INPUT_H * INPUT_W; i++) {
    std::cout << (" .:-=+*#%@"[target_buffer_[i] * 255 / 26])
              << (((i + 1) % INPUT_W) ? "" : "\n");
  }
}
