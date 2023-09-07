#ifndef CMAKE_SAMPLE_MNIST_
#define CMAKE_SAMPLE_MNIST_
#include <NvInfer.h>
#include <NvOnnxParser.h>
#include <cuda_fp16.h>
#include <cuda_runtime_api.h>
#include <unistd.h>

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
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
  void log(Severity severity, nvinfer1::AsciiChar const* msg) noexcept {
    if (severity != Severity::kINFO) {
      std::cout << "TensorRT: " << msg << std::endl;
    }
  }
};

class Node {
 public:
  ~Node() = default;
  Node(int argc, char* argv[]) : ok_(true) { ParserArgs(argc, argv); }

  /// 初始化数据
  void Init();

  /// 构建
  void Build();

  /// 推理
  void Inference();

  /// 销毁数据
  void Destroy();

 private:
  // 解析参数
  void ParserArgs(int argc, char* argv[]);

  std::string DataTypeToString(nvinfer1::DataType dataType);

  size_t DataTypeToSize(nvinfer1::DataType dataType);

  // 解析模型文件
  void ParserModelFile();

  // 解析Engine文件
  void ParserPlanFile();

  /// 加载输入的图片
  void LoadInputImages();

  // 将原始图片中的像素用二进制文本 “.:-=+*#%@”来输出
  void PrintInputImages();

  // 打印推理结果
  void PrintRestult(float* output_buffer_h);

  bool ok_;

  // log
  Logger logger_;

  // engine
  nvinfer1::ICudaEngine* engine_;

  std::vector<char> engine_string_;

  static const int INPUT_H = 28;

  static const int INPUT_W = 28;

  static const int OUTPUT_SIZE = 10;

  uint8_t image_buffer_[INPUT_H * INPUT_W];

  std::string model_path_ = "./data/mnist.onnx";
  std::string plan_path_ = "./data/mnist.plan";
  std::string image_path_;
};

#endif  // CMAKE_SAMPLE_MNIST_
