#include "node.h"

void Node::Init() {
  if (!ok_) return;
}

void Node::Build() {
  if (!ok_) return;
  LoadInputImages();
  PrintInputImages();
  ParserModelFile();
  ParserPlanFile();
}

void Node::Inference() {
  if (!ok_) return;
  nvinfer1::IRuntime* runtime{nvinfer1::createInferRuntime(logger_)};
  engine_ = runtime->deserializeCudaEngine(engine_string_.data(),
                                           engine_string_.size());
  if (!engine_) {
    std::cout << "Failed loading engine!" << std::endl;
    return;
  }

  // 2. context
  // 一个引擎可以有多个执行上下文，允许将一组权重用于多个重叠的推理任务
  nvinfer1::IExecutionContext* context = engine_->createExecutionContext();

  // 3. buffer
  // engine中输入和输出张量的总数量
  // 绑定的顺序通常是这样的：先是所有的输入绑定，然后是所有的输出绑定
  // 也就是说: 在张量的数组中, 前半部分全是输入张量的index,
  // 后半部分全是输出张量的index
  long unsigned int num_io_tensors = engine_->getNbIOTensors();
  // 输入张量的数量
  long unsigned int n_input_tensors = 0;  // mnist模型的输入张量是1
  // 输出张量的数量
  long unsigned int n_output_tensors = 0;  // mnist模型的输出张量是1
  // 张量名
  std::vector<std::string> tensor_name(num_io_tensors);
  for (int i = 0; i < num_io_tensors; i++) {
    tensor_name[i] = std::string(engine_->getIOTensorName(i));
    std::cout << "tensor name" << i << ":" << tensor_name[i] << std::endl;
    // 张量数量自增
    if (nvinfer1::TensorIOMode::kINPUT ==
        engine_->getTensorIOMode(tensor_name[i].c_str())) {
      n_input_tensors++;
    } else if (nvinfer1::TensorIOMode::kOUTPUT ==
               engine_->getTensorIOMode(tensor_name[i].c_str())) {
      n_output_tensors++;
    }
  }

  // 设置输入张量的形状: 4:张量的维度数量，{1, 1, x, y} 表示各个维度的大小。
  context->setInputShape(tensor_name[0].c_str(),
                         nvinfer1::Dims32{4, {1, 1, INPUT_H, INPUT_W}});

  std::vector<int> tensor_size(num_io_tensors, 0);  // 每个张量的大小
  // 遍历所有张量, 计算每个张量需要开辟的空间
  for (int i = 0; i < num_io_tensors; ++i) {
    // 获取张量形状
    nvinfer1::Dims32 dim = context->getTensorShape(tensor_name[i].c_str());
    int size = 1;
    // 遍历张量每个维度
    for (int j = 0; j < dim.nbDims; ++j) {
      size *= dim.d[j];  // 每个维度的长度
    }
    // getTensorDataType: 获取指定张量的数据类型
    tensor_size[i] =
        size *
        DataTypeToSize(engine_->getTensorDataType(tensor_name[i].c_str()));
  }

  // // buffer
  std::vector<void*> buffer_h{num_io_tensors, nullptr};
  std::vector<void*> buffer_d{num_io_tensors, nullptr};
  // 遍历所有张量: host和device的所有内存开辟空间
  for (int i = 0; i < num_io_tensors; ++i) {
    // host
    buffer_h[i] = (void*)new char[tensor_size[i]];
    // device
    CHECK(cudaMalloc(&buffer_d[i], tensor_size[i]));
  }

  // 为输入张量分配内存并填充数据
  float* p_image_buffer = (float*)buffer_h[0];  // 指向host buffer的指针
  for (int i = 0; i < INPUT_H * INPUT_W; ++i) {
    // 黑底白字 + 归一化
    p_image_buffer[i] = 1.0 - float(image_buffer_[i] / 255.0);
  }

  // copy buffer host to device
  for (int i = 0; i < n_input_tensors; ++i) {
    CHECK(cudaMemcpy(buffer_d[i], buffer_h[i], tensor_size[i],
                     cudaMemcpyHostToDevice));
  }
  for (int i = 0; i < num_io_tensors; ++i) {
    // 绑定张量的地址，即将内存缓冲区的地址与特定张量关联起来
    context->setTensorAddress(tensor_name[i].c_str(), buffer_d[i]);
  }

  // 4. execute
  // 推理: 异步
  bool status = context->enqueueV3(0);  //  0 表示默认的CUDA流

  // 推理: 同步, 推理操作会阻塞执行线程，直到推理完成
  // bool status = context->executeV2(buffer_d.data());

  if (!status) {
    std::cout << "inference fault" << std::endl;
    return;
  }

  // copy buffer device to host
  for (int i = n_input_tensors; i < num_io_tensors; ++i) {
    CHECK(cudaMemcpy(buffer_h[i], buffer_d[i], tensor_size[i],
                     cudaMemcpyDeviceToHost));
  }

  // 打印推理结果
  PrintRestult((float*)buffer_h[1]);

  // free buffer
  for (int i = 0; i < num_io_tensors; ++i) {
    delete[] (char*)buffer_h[i];
    CHECK(cudaFree(buffer_d[i]));
  }
}

void Node::Destroy() {
  if (!ok_) return;
  ok_ = true;
}

void Node::ParserArgs(int argc, char* argv[]) {
  if (1 == argc) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 9);
    int random_value = dis(gen);
    image_path_ = std::string("./data/mnist/") + std::to_string(random_value) +
                  std::string(".pgm");

  } else if (2 == argc) {
    image_path_ = argv[1];
  } else {
    ok_ = false;
  }
  std::cout << "image path: " << image_path_ << std::endl;
}

std::string Node::DataTypeToString(nvinfer1::DataType dataType) {
  switch (dataType) {
    case nvinfer1::DataType::kFLOAT:
      return std::string("FP32 ");
    case nvinfer1::DataType::kHALF:
      return std::string("FP16 ");
    case nvinfer1::DataType::kINT8:
      return std::string("INT8 ");
    case nvinfer1::DataType::kINT32:
      return std::string("INT32");
    case nvinfer1::DataType::kBOOL:
      return std::string("BOOL ");
    default:
      return std::string("Unknown");
  }
}

size_t Node::DataTypeToSize(nvinfer1::DataType dataType) {
  switch ((int)dataType) {
    case int(nvinfer1::DataType::kFLOAT):
      return 4;
    case int(nvinfer1::DataType::kHALF):
      return 2;
    case int(nvinfer1::DataType::kINT8):
      return 1;
    case int(nvinfer1::DataType::kINT32):
      return 4;
    case int(nvinfer1::DataType::kBOOL):
      return 1;
    default:
      return 4;
  }
}

void Node::ParserModelFile() {
  if (0 == access(plan_path_.c_str(), F_OK)) {
    return;
  }
  // 没有plan文件
  std::cout << "没有plan文件" << std::endl;
  // 1. builder
  nvinfer1::IBuilder* builder = nvinfer1::createInferBuilder(logger_);

  // 2. config
  nvinfer1::IBuilderConfig* config = builder->createBuilderConfig();
  config->setMemoryPoolLimit(nvinfer1::MemoryPoolType::kWORKSPACE, 1 << 30);

  // 3. network
  nvinfer1::INetworkDefinition* network = builder->createNetworkV2(
      1U << int(nvinfer1::NetworkDefinitionCreationFlag::kEXPLICIT_BATCH));

  // 4. parser
  // parse onnx model file
  nvonnxparser::IParser* parser = nvonnxparser::createParser(*network, logger_);
  if (!parser->parseFromFile(
          model_path_.c_str(),
          static_cast<int>(nvinfer1::ILogger::Severity::kINFO))) {
    return;
  }

  // 5. serialized network
  nvinfer1::IHostMemory* serialized_model =
      builder->buildSerializedNetwork(*network, *config);
  if (nullptr == serialized_model || 0 == serialized_model->size()) {
    std::cout << "Failed building serialized engine!" << std::endl;
    return;
  }

  // 6. plan
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
  std::ifstream infile(image_path_, std::ifstream::binary);
  std::string magic, h, w, max;
  infile >> magic >> h >> w >> max;
  infile.seekg(1, infile.cur);
  infile.read(reinterpret_cast<char*>(image_buffer_), INPUT_H * INPUT_W);
}

void Node::PrintInputImages() {
  std::cout << "\nInput:\n" << std::endl;
  for (int i = 0; i < INPUT_H * INPUT_W; i++) {
    std::cout << (" .:-=+*#%@"[image_buffer_[i] / 26])
              << (((i + 1) % INPUT_W) ? "" : "\n");
  }
}

void Node::PrintRestult(float* output_buffer_h) {
  double sum = 0.0;
  double buffer[OUTPUT_SIZE];

  // 计算指数部分的和
  for (int i = 0; i < OUTPUT_SIZE; i++) {
    sum += exp(output_buffer_h[i]);
  }

  // 计算softmax概率
  std::cout << "Optput:" << std::endl;
  for (int i = 0; i < OUTPUT_SIZE; i++) {
    buffer[i] = exp(output_buffer_h[i]) / sum;
    std::cout << " Prob " << i << "  " << std::fixed << std::setw(5)
              << std::setprecision(4) << buffer[i] << " "
              << "Class " << i << ": "
              << std::string(int(std::floor(buffer[i] * 10 + 0.5f)), '*')
              << std::endl;
  }
}
