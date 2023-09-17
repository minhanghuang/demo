#include "dynamic-reshape.h"

void DynamicReshape::Init(int argc, char* argv[]) {
  if (!ok_) return;
  ParserArgs(argc, argv);
}

void DynamicReshape::Build() {
  if (!ok_) return;
  std::cout << "      --------                --------- " << std::endl;
  std::cout << "      --------                --------- " << std::endl;
  std::cout << "      --------     build      --------- " << std::endl;
  std::cout << "      --------                --------- " << std::endl;
  std::cout << "      --------                --------- " << std::endl;
  nvinfer1::IBuilder* builder = nvinfer1::createInferBuilder(logger_);
  nvinfer1::IRuntime* runtime = nvinfer1::createInferRuntime(logger_);
  LoadInputImages();
  PrintImages255(image_buffer_.data(), input_image_h_, input_image_w_);
  BuildInferEngine(builder, runtime);
  BuildReshapeEngine(builder, runtime);
}

void DynamicReshape::Inference() {
  if (!ok_) return;

  std::cout << "      --------                --------- " << std::endl;
  std::cout << "      --------                --------- " << std::endl;
  std::cout << "      --------   inference    --------- " << std::endl;
  std::cout << "      --------                --------- " << std::endl;
  std::cout << "      --------                --------- " << std::endl;

  /// input image dims
  nvinfer1::Dims32 dims_image = mnist_input_dims_;
  dims_image.d[2] = input_image_h_;
  dims_image.d[3] = input_image_w_;

  /// buffer
  BufferManage::Buffer reshape_buffer;
  BufferManage::Buffer mnist_input_buffer;
  BufferManage::Buffer mnist_output_buffer;

  /// reshape inference
  nvinfer1::IExecutionContext* reshape_context =
      reshape_engine_->createExecutionContext();
  nvinfer1::IExecutionContext* context = engine_->createExecutionContext();

  reshape_context->setInputShape(reshape_engine_->getIOTensorName(0),
                                 dims_image);
  context->setInputShape(engine_->getIOTensorName(0), mnist_input_dims_);

  std::cout << "reshape set input shape: "
            << reshape_engine_->getIOTensorName(0) << ": ";
  PrintDims32(dims_image);
  std::cout << "set input shape: " << engine_->getIOTensorName(0) << ": ";
  PrintDims32(mnist_input_dims_);

  std::vector<std::string> tensor_reshape_name(2);
  std::vector<std::string> tensor_name(2);
  tensor_reshape_name[0] = std::string(reshape_engine_->getIOTensorName(0));
  tensor_reshape_name[1] = std::string(reshape_engine_->getIOTensorName(1));
  tensor_name[0] = std::string(engine_->getIOTensorName(0));
  tensor_name[1] = std::string(engine_->getIOTensorName(1));
  std::cout << "tensor_reshape_name: " << tensor_reshape_name[0] << std::endl;
  std::cout << "tensor_reshape_name: " << tensor_reshape_name[1] << std::endl;
  std::cout << "tensor_name: " << tensor_name[0] << std::endl;
  std::cout << "tensor_name: " << tensor_name[1] << std::endl;

  std::vector<int> tensor_reshape_size(2, 0);
  std::vector<int> tensor_size(2, 0);
  // 输入张量大小
  tensor_reshape_size[0] = input_image_h_ * input_image_w_ *
                           DataTypeToSize(reshape_engine_->getTensorDataType(
                               tensor_reshape_name[0].c_str()));
  // 输出张量大小
  tensor_reshape_size[1] = CalcVolume(mnist_input_dims_) *
                           DataTypeToSize(reshape_engine_->getTensorDataType(
                               tensor_reshape_name[1].c_str()));
  tensor_size[0] = tensor_reshape_size[1];
  tensor_size[1] =
      CalcVolume(mnist_output_dims_) *
      DataTypeToSize(engine_->getTensorDataType(tensor_name[1].c_str()));
  std::cout << "reshape 输入张量大小: " << tensor_reshape_size[0] << std::endl;
  std::cout << "reshape 输出张量大小: " << tensor_reshape_size[1] << std::endl;
  std::cout << "输入张量大小: " << tensor_size[0] << std::endl;
  std::cout << "输出张量大小: " << tensor_size[1] << std::endl;

  reshape_buffer.host = (void*)new char[tensor_reshape_size[0]];
  CHECK(cudaMalloc(&reshape_buffer.device, tensor_reshape_size[0]));
  mnist_input_buffer.host = (void*)new char[tensor_reshape_size[1]];
  CHECK(cudaMalloc(&mnist_input_buffer.device, tensor_reshape_size[1]));
  mnist_output_buffer.host = (void*)new char[tensor_size[1]];
  CHECK(cudaMalloc(&mnist_output_buffer.device, tensor_size[1]));

  std::cout << "reshape host address: " << reshape_buffer.host << std::endl;
  std::cout << "reshape device address: " << reshape_buffer.device << std::endl;
  std::cout << "input host address: " << mnist_input_buffer.host << std::endl;
  std::cout << "input device address: " << mnist_input_buffer.device
            << std::endl;
  std::cout << "output host address: " << mnist_output_buffer.host << std::endl;
  std::cout << "output device address: " << mnist_output_buffer.device
            << std::endl;

  // 为输入张量分配内存并填充数据
  float* p_image_buffer = (float*)reshape_buffer.host;
  for (int i = 0; i < input_image_h_ * input_image_w_; ++i) {
    p_image_buffer[i] = float(image_buffer_[i]);
  }

  // copy buffer host to device
  CHECK(cudaMemcpy(reshape_buffer.device, reshape_buffer.host,
                   tensor_reshape_size[0], cudaMemcpyHostToDevice));
  CHECK(cudaMemcpy(mnist_input_buffer.device, mnist_input_buffer.host,
                   tensor_reshape_size[1], cudaMemcpyHostToDevice));
  CHECK(cudaMemcpy(mnist_output_buffer.device, mnist_output_buffer.host,
                   tensor_size[1], cudaMemcpyHostToDevice));

  // 绑定张量的地址，将GPU内存与张量关联起来
  reshape_context->setTensorAddress(tensor_reshape_name[0].c_str(),
                                    reshape_buffer.device);
  reshape_context->setTensorAddress(tensor_reshape_name[1].c_str(),
                                    mnist_input_buffer.device);
  context->setTensorAddress(tensor_name[0].c_str(), mnist_input_buffer.device);

  std::cout << "address: " << tensor_reshape_name[0] << " -> "
            << reshape_buffer.device << std::endl;
  std::cout << "address: " << tensor_reshape_name[1] << " -> "
            << mnist_input_buffer.device << std::endl;
  std::cout << "address: " << tensor_name[0] << " -> "
            << mnist_input_buffer.device << std::endl;
  std::cout << "address: " << tensor_name[1] << " -> "
            << mnist_output_buffer.device << std::endl;

  /// reshape 推理
  std::vector<void*> reshape_bindings = {reshape_buffer.device,
                                         mnist_input_buffer.device};
  bool status = reshape_context->executeV2(reshape_bindings.data());
  if (!status) {
    std::cout << "Failed reshape inference" << std::endl;
    return;
  }

  /// copy buffer device to host
  CHECK(cudaMemcpy(reshape_buffer.host, reshape_buffer.device,
                   tensor_reshape_size[0], cudaMemcpyDeviceToHost));
  CHECK(cudaMemcpy(mnist_input_buffer.host, mnist_input_buffer.device,
                   tensor_reshape_size[1], cudaMemcpyDeviceToHost));

  std::cout << "reshape inference output:" << std::endl;
  PrintImages255((float*)mnist_input_buffer.host, mnist_input_dims_.d[2],
                 mnist_input_dims_.d[3]);

  p_image_buffer = static_cast<float*>(mnist_input_buffer.host);
  for (int i = 0; i < mnist_input_dims_.d[2] * mnist_input_dims_.d[3]; ++i) {
    // 黑底白字 归一化
    p_image_buffer[i] = 1.0 - static_cast<float>(p_image_buffer[i] / 255.0);
  }

  CHECK(cudaMemcpy(mnist_input_buffer.device, mnist_input_buffer.host,
                   tensor_size[0], cudaMemcpyHostToDevice));

  context->setTensorAddress(tensor_name[1].c_str(), mnist_output_buffer.device);

  std::vector<void*> bindings = {mnist_input_buffer.device,
                                 mnist_output_buffer.device};

  /// mnist推理
  status = context->executeV2(bindings.data());
  if (!status) {
    std::cout << "Failed inference" << std::endl;
    return;
  }
  CHECK(cudaMemcpy(mnist_output_buffer.host, mnist_output_buffer.device,
                   tensor_size[1], cudaMemcpyDeviceToHost));

  /// 打印推理结果
  PrintRestult((float*)mnist_output_buffer.host);
}

void DynamicReshape::ParserArgs(int argc, char* argv[]) {
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

size_t DynamicReshape::DataTypeToSize(nvinfer1::DataType dataType) {
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

int64_t DynamicReshape::CalcVolume(const nvinfer1::Dims& d) {
  return std::accumulate(d.d, d.d + d.nbDims, int64_t{1},
                         std::multiplies<int64_t>{});
}

void DynamicReshape::BuildInferEngine(nvinfer1::IBuilder* builder,
                                      nvinfer1::IRuntime* runtime) {
  if (!ok_) return;
  if (0 != access(plan_path_.c_str(), F_OK)) {
    std::cout << "没有plan文件" << std::endl;
    /// config
    nvinfer1::IBuilderConfig* config = builder->createBuilderConfig();
    config->setMemoryPoolLimit(nvinfer1::MemoryPoolType::kWORKSPACE, 1 << 30);

    /// network
    nvinfer1::INetworkDefinition* network = builder->createNetworkV2(
        1U << static_cast<int>(
            nvinfer1::NetworkDefinitionCreationFlag::kEXPLICIT_BATCH));

    /// parser
    nvonnxparser::IParser* parser =
        nvonnxparser::createParser(*network, logger_);
    if (!parser->parseFromFile(
            model_path_.c_str(),
            static_cast<int>(nvinfer1::ILogger::Severity::kINFO))) {
      return;
    }

    /// serialized network
    nvinfer1::IHostMemory* serialized_model =
        builder->buildSerializedNetwork(*network, *config);
    if (nullptr == serialized_model || 0 == serialized_model->size()) {
      std::cout << "Failed building serialized engine!" << std::endl;
      return;
    }

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
  }

  /// 读取engine序列化文件
  std::ifstream plan_file(plan_path_, std::ios::binary);
  std::vector<char> engine_string;
  long int fsize = 0;
  plan_file.seekg(0, plan_file.end);
  fsize = plan_file.tellg();
  plan_file.seekg(0, plan_file.beg);
  engine_string.resize(fsize);
  plan_file.read(engine_string.data(), engine_string.size());

  // 创建engine
  engine_ = runtime->deserializeCudaEngine(engine_string.data(),
                                           engine_string.size());
  if (!engine_) {
    std::cout << "Failed deserialize engine" << std::endl;
    ok_ = false;
    return;
  }
  nvinfer1::Dims32 dims_in =
      engine_->getTensorShape(engine_->getIOTensorName(0));
  nvinfer1::Dims32 dims_out =
      engine_->getTensorShape(engine_->getIOTensorName(1));
  std::cout << "in dims: ";
  PrintDims32(dims_in);
  std::cout << "out dims: ";
  PrintDims32(dims_out);
}

void DynamicReshape::BuildReshapeEngine(nvinfer1::IBuilder* builder,
                                        nvinfer1::IRuntime* runtime) {
  if (!ok_) return;
  nvinfer1::Dims dims_in;

  const int32_t infer_tensor_number = engine_->getNbIOTensors();
  dims_in = engine_->getTensorShape(engine_->getIOTensorName(0));

  /// newtwork
  nvinfer1::INetworkDefinition* network = builder->createNetworkV2(
      1U << static_cast<int>(
          nvinfer1::NetworkDefinitionCreationFlag::kEXPLICIT_BATCH));

  // config
  nvinfer1::IBuilderConfig* config = builder->createBuilderConfig();
  config->setMemoryPoolLimit(nvinfer1::MemoryPoolType::kWORKSPACE, 1 << 20);

  // input layer
  nvinfer1::ITensor* tensor_in = network->addInput(
      "input", nvinfer1::DataType::kFLOAT, nvinfer1::Dims4{-1, 1, -1, -1});
  auto input_layer = network->addResize(*tensor_in);
  input_layer->setOutputDimensions(dims_in);
  network->markOutput(*input_layer->getOutput(0));

  /// profile
  nvinfer1::IOptimizationProfile* profile =
      builder->createOptimizationProfile();
  profile->setDimensions(tensor_in->getName(),
                         nvinfer1::OptProfileSelector::kMIN,
                         nvinfer1::Dims4{1, 1, 1, 1});
  profile->setDimensions(tensor_in->getName(),
                         nvinfer1::OptProfileSelector::kOPT,
                         nvinfer1::Dims4{1, 1, 28, 28});
  profile->setDimensions(tensor_in->getName(),
                         nvinfer1::OptProfileSelector::kMAX,
                         nvinfer1::Dims4{1, 1, 56, 56});
  config->addOptimizationProfile(profile);

  nvinfer1::IHostMemory* serialized_model =
      builder->buildSerializedNetwork(*network, *config);
  if (nullptr == serialized_model || 0 == serialized_model->size()) {
    std::cout << "Failed building reshape serialized engine!" << std::endl;
    return;
  }

  /// 创建engine
  reshape_engine_ = runtime->deserializeCudaEngine(serialized_model->data(),
                                                   serialized_model->size());
  if (!reshape_engine_) {
    std::cout << "Failed deserialize reshape engine" << std::endl;
    ok_ = false;
    return;
  }

  // debug
  std::cout << "reshape engine tensor number: "
            << reshape_engine_->getNbIOTensors() << std::endl;
  std::cout << "reshape engine input tensor name: "
            << reshape_engine_->getIOTensorName(0) << std::endl;
  std::cout << "reshape engine output tensor name: "
            << reshape_engine_->getIOTensorName(1) << std::endl;
  nvinfer1::Dims32 reshape_dims_in =
      reshape_engine_->getTensorShape(reshape_engine_->getIOTensorName(0));
  nvinfer1::Dims32 reshape_dims_out =
      reshape_engine_->getTensorShape(reshape_engine_->getIOTensorName(1));
  std::cout << "reshape in dims: ";
  PrintDims32(reshape_dims_in);
  std::cout << "reshape out dims: ";
  PrintDims32(reshape_dims_out);
}

void DynamicReshape::ParseModelFile() {
  /// build
  nvinfer1::IBuilder* builder = nvinfer1::createInferBuilder(logger_);
  nvinfer1::Dims dims_in;
  nvinfer1::Dims dims_out;

  if (0 != access(plan_path_.c_str(), F_OK)) {
    std::cout << "没有plan文件" << std::endl;
    /// config
    nvinfer1::IBuilderConfig* config = builder->createBuilderConfig();
    config->setMemoryPoolLimit(nvinfer1::MemoryPoolType::kWORKSPACE, 1 << 30);

    /// network
    nvinfer1::INetworkDefinition* network = builder->createNetworkV2(
        1U << static_cast<int>(
            nvinfer1::NetworkDefinitionCreationFlag::kEXPLICIT_BATCH));

    /// parser
    nvonnxparser::IParser* parser =
        nvonnxparser::createParser(*network, logger_);
    if (!parser->parseFromFile(
            model_path_.c_str(),
            static_cast<int>(nvinfer1::ILogger::Severity::kINFO))) {
      return;
    }
    dims_in = network->getInput(0)->getDimensions();
    dims_out = network->getOutput(0)->getDimensions();

    /// serialized network
    nvinfer1::IHostMemory* serialized_model =
        builder->buildSerializedNetwork(*network, *config);
    if (nullptr == serialized_model || 0 == serialized_model->size()) {
      std::cout << "Failed building serialized engine!" << std::endl;
      return;
    }

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
  }

  /// dynamic shape engine
  nvinfer1::INetworkDefinition* reshape_network = builder->createNetworkV2(
      1U << static_cast<int>(
          nvinfer1::NetworkDefinitionCreationFlag::kEXPLICIT_BATCH));

  nvinfer1::IBuilderConfig* reshape_config = builder->createBuilderConfig();
  reshape_config->setMemoryPoolLimit(nvinfer1::MemoryPoolType::kWORKSPACE,
                                     1 << 20);

  nvinfer1::ITensor* new_tensor_in = reshape_network->addInput(
      "input", nvinfer1::DataType::kFLOAT, nvinfer1::Dims4{-1, 1, -1, -1});
  auto reshape_layer = reshape_network->addResize(*new_tensor_in);
  reshape_layer->setOutputDimensions(dims_in);
  reshape_network->markOutput(*reshape_layer->getOutput(0));

  nvinfer1::IOptimizationProfile* profile =
      builder->createOptimizationProfile();
  profile->setDimensions(new_tensor_in->getName(),
                         nvinfer1::OptProfileSelector::kMIN,
                         nvinfer1::Dims4{1, 1, 1, 1});
  profile->setDimensions(new_tensor_in->getName(),
                         nvinfer1::OptProfileSelector::kOPT,
                         nvinfer1::Dims4{1, 1, 28, 28});
  profile->setDimensions(new_tensor_in->getName(),
                         nvinfer1::OptProfileSelector::kMAX,
                         nvinfer1::Dims4{1, 1, 56, 56});
  reshape_config->addOptimizationProfile(profile);

  nvinfer1::IHostMemory* reshape_serialized_model =
      builder->buildSerializedNetwork(*reshape_network, *reshape_config);
  if (nullptr == reshape_serialized_model ||
      0 == reshape_serialized_model->size()) {
    std::cout << "Failed building reshape serialized engine!" << std::endl;
    return;
  }

  delete builder;
}

void DynamicReshape::LoadInputImages() {
  std::ifstream infile(image_path_, std::ifstream::binary);
  std::string magic;
  int h, w, max;
  infile >> magic >> h >> w >> max;
  infile.seekg(1, infile.cur);
  nvinfer1::Dims4 input_dims{1, 1, h, w};
  input_image_h_ = h;
  input_image_w_ = w;
  std::cout << "{H, W} " << input_image_h_ << "," << input_image_w_
            << std::endl;
  size_t vol = CalcVolume(input_dims);
  std::vector<uint8_t> file_data(vol);
  image_buffer_.resize(vol);
  infile.read(reinterpret_cast<char*>(image_buffer_.data()), vol);
}

void DynamicReshape::PrintImages255(const unsigned char* data, int h, int w) {
  std::cout << "\nData:" << std::endl;
  for (int i = 0; i < h * w; i++) {
    std::cout << (" .:-=+*#%@"[data[i] / 26]) << (((i + 1) % w) ? "" : "\n");
  }
}

void DynamicReshape::PrintImages255(const float* data, int h, int w) {
  std::cout << "\nData:" << std::endl;
  for (int i = 0; i < h * w; i++) {
    std::cout << (" .:-=+*#%@"[static_cast<int>(data[i] / 26)])
              << (((i + 1) % w) ? "" : "\n");
  }
}

void DynamicReshape::PrintRestult(float* buffer_host) {
  double sum = 0.0;
  double buffer[10];

  // 计算指数部分的和
  for (int i = 0; i < 10; i++) {
    sum += exp(buffer_host[i]);
  }

  // 计算softmax概率
  std::cout << "Optput:" << std::endl;
  for (int i = 0; i < 10; i++) {
    buffer[i] = exp(buffer_host[i]) / sum;
    std::cout << " Prob " << i << "  " << std::fixed << std::setw(5)
              << std::setprecision(4) << buffer[i] << " "
              << "Class " << i << ": "
              << std::string(int(std::floor(buffer[i] * 10 + 0.5f)), '*')
              << std::endl;
  }
}

void DynamicReshape::PrintDims32(nvinfer1::Dims32 dims) {
  std::cout << "[";
  for (int i = 0; i < dims.nbDims; i++) {
    std::cout << dims.d[i];
    if (i != dims.nbDims - 1) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;
}
