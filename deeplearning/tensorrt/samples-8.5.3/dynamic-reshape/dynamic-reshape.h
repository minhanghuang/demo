#ifndef SAMPLE_DYNAMIC_RESHAPE_
#define SAMPLE_DYNAMIC_RESHAPE_
#include <NvInfer.h>
#include <NvInferImpl.h>
#include <NvInferRuntime.h>
#include <NvOnnxParser.h>
#include <cuda_fp16.h>
#include <cuda_runtime_api.h>
#include <unistd.h>

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <thread>
#include <vector>

#define CHECK(call) check(call, __LINE__, __FILE__)
inline bool check(cudaError_t e, int i_line, const char* sz_file) {
  if (e != cudaSuccess) {
    std::cout << "CUDA runtime API error " << cudaGetErrorName(e) << " at line "
              << i_line << " in file " << sz_file << std::endl;
    return false;
  }
  return true;
}

class Logger : public nvinfer1::ILogger {
 public:
  void log(Severity severity, nvinfer1::AsciiChar const* msg) noexcept {
    if (severity != Severity::kINFO) {
      // std::cout << "TensorRT: " << msg << std::endl;
    }
  }
  void log(nvinfer1::AsciiChar const* msg) noexcept {
    std::cout << "TensorRT: " << msg << std::endl;
  }
};

enum Location : int32_t {
  kDevice = static_cast<int32_t>(nvinfer1::TensorLocation::kDEVICE),
  kHost = static_cast<int32_t>(nvinfer1::TensorLocation::kHOST),
};

class BufferManage {
 public:
  struct Buffer {
    void* device = nullptr;
    void* host = nullptr;
  };
  BufferManage() = default;
  ~BufferManage() {
    std::cout << "free buffer" << std::endl;
    free(buffer_reshape_.host);
    free(buffer_mnist_input_.host);
    free(buffer_mnist_output_.host);
    CHECK(cudaFree(buffer_reshape_.device));
    CHECK(cudaFree(buffer_mnist_input_.device));
    CHECK(cudaFree(buffer_mnist_output_.device));
  }

  void set_buffer_reshape(Buffer buffer);

  void set_buffer_mnist_input(Buffer buffer);

  void set_buffer_mnist_output(Buffer buffer);

  Buffer buffer_reshape();

  Buffer buffer_mnist_input();

  Buffer buffer_mnist_output();

 private:
  Buffer buffer_reshape_;

  Buffer buffer_mnist_input_;

  Buffer buffer_mnist_output_;
};

class DynamicReshape {
 public:
  ~DynamicReshape() = default;
  DynamicReshape() : ok_(true) {}

  /// 初始化数据
  void Init(int argc, char* argv[]);

  /// 构建
  void Build();

  /// 推理
  void Inference();

 private:
  // 解析参数
  void ParserArgs(int argc, char* argv[]);

  size_t DataTypeToSize(nvinfer1::DataType dataType);

  // 计算Dims体积
  int64_t CalcVolume(const nvinfer1::Dims& d);

  // 构建推理engine
  void BuildInferEngine(nvinfer1::IBuilder*, nvinfer1::IRuntime*);

  // 构建动态重塑engine
  void BuildReshapeEngine(nvinfer1::IBuilder*, nvinfer1::IRuntime*);

  // 解析模型文件
  void ParseModelFile();

  /// 加载输入的图片
  void LoadInputImages();

  // 将原始图片中的像素用二进制文本 “.:-=+*#%@”来输出
  void PrintImages255(const unsigned char* data, int h, int w);

  void PrintImages255(const float* data, int h, int w);

  // 打印推理结果
  void PrintRestult(float* buffer_host);

  // 打印Dims
  void PrintDims32(nvinfer1::Dims32);

  bool ok_;

  Logger logger_;

  nvinfer1::ICudaEngine* engine_;

  nvinfer1::ICudaEngine* reshape_engine_;

  std::vector<char> engine_string_;

  int input_image_h_;

  int input_image_w_;

  std::vector<unsigned char> image_buffer_;

  std::string model_path_ = "./data/mnist/mnist.onnx";

  std::string plan_path_ = "./data/mnist/dynamic-reshape.plan";

  std::string image_path_;

  BufferManage buffer_;

  const nvinfer1::Dims32 mnist_input_dims_ = {4, {1, 1, 28, 28}};

  const nvinfer1::Dims32 mnist_output_dims_ = {2, {1, 10}};
};

#endif  // SAMPLE_DYNAMIC_RESHAPE_
