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

using namespace nvinfer1;

#define CHECK(call) check(call, __LINE__, __FILE__)

inline bool check(cudaError_t e, int i_line, const char* sz_file) {
  if (e != cudaSuccess) {
    std::cout << "CUDA runtime API error " << cudaGetErrorName(e) << " at line "
              << i_line << " in file " << sz_file << std::endl;
    return false;
  }
  return true;
}

class Logger : public ILogger {
  void log(Severity severity, AsciiChar const* msg) noexcept {
    if (severity != Severity::kINFO) {
      std::cout << "TensorRT: " << msg << std::endl;
    }
  }
};

template <typename T>
void printArrayRecursion(const T* pArray, Dims32 dim, int iDim, int iStart) {
  if (iDim == dim.nbDims - 1) {
    for (int i = 0; i < dim.d[iDim]; ++i) {
      std::cout << std::fixed << std::setprecision(3) << std::setw(6)
                << double(pArray[iStart + i]) << " ";
    }
  } else {
    int nElement = 1;
    for (int i = iDim + 1; i < dim.nbDims; ++i) {
      nElement *= dim.d[i];
    }
    for (int i = 0; i < dim.d[iDim]; ++i) {
      printArrayRecursion<T>(pArray, dim, iDim + 1, iStart + i * nElement);
    }
  }
  std::cout << std::endl;
  return;
}

template <typename T>
void printArrayInformation(const T* pArray, Dims32 dim,
                           std::string name = std::string(""),
                           bool bPrintArray = false, int n = 10) {
  // print shape information
  std::cout << std::endl;
  std::cout << name << ": (";
  for (int i = 0; i < dim.nbDims; ++i) {
    std::cout << dim.d[i] << ", ";
  }
  std::cout << ")" << std::endl;

  // print statistic information
  int nElement = 1;  // number of elements with batch dimension
  for (int i = 0; i < dim.nbDims; ++i) {
    nElement *= dim.d[i];
  }

  double sum = double(pArray[0]);
  double absSum = double(fabs(double(pArray[0])));
  double sum2 = double(pArray[0]) * double(pArray[0]);
  double diff = 0.0;
  double maxValue = double(pArray[0]);
  double minValue = double(pArray[0]);
  for (int i = 1; i < nElement; ++i) {
    sum += double(pArray[i]);
    absSum += double(fabs(double(pArray[i])));
    sum2 += double(pArray[i]) * double(pArray[i]);
    maxValue = double(pArray[i]) > maxValue ? double(pArray[i]) : maxValue;
    minValue = double(pArray[i]) < minValue ? double(pArray[i]) : minValue;
    diff += std::abs(double(pArray[i]) - double(pArray[i - 1]));
  }
  double mean = sum / nElement;
  double var = sum2 / nElement - mean * mean;

  std::cout << "absSum=" << std::fixed << std::setprecision(4) << std::setw(7)
            << absSum << ",";
  std::cout << "mean=" << std::fixed << std::setprecision(4) << std::setw(7)
            << mean << ",";
  std::cout << "var=" << std::fixed << std::setprecision(4) << std::setw(7)
            << var << ",";
  std::cout << "max=" << std::fixed << std::setprecision(4) << std::setw(7)
            << maxValue << ",";
  std::cout << "min=" << std::fixed << std::setprecision(4) << std::setw(7)
            << minValue << ",";
  std::cout << "diff=" << std::fixed << std::setprecision(4) << std::setw(7)
            << diff << ",";
  std::cout << std::endl;

  // print first n element and last n element
  for (int i = 0; i < n; ++i) {
    std::cout << std::fixed << std::setprecision(5) << std::setw(8)
              << double(pArray[i]) << ", ";
  }
  std::cout << std::endl;
  for (int i = nElement - n; i < nElement; ++i) {
    std::cout << std::fixed << std::setprecision(5) << std::setw(8)
              << double(pArray[i]) << ", ";
  }
  std::cout << std::endl;

  // print the whole array
  if (bPrintArray) {
    printArrayRecursion<T>(pArray, dim, 0, 0);
  }

  return;
}

static void PrintRestult(float* output_buffer) {
  float val{0.0f};
  int idx{0};
  float sum{0.0f};
}

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
  void ParserArgs(int argc, char* argv[]);

  void ParserModelFile();

  void ParserPlanFile();

  /// 加载图片
  void LoadInputImages();

  // 将原始图片中的像素用二进制文本 “.:-=+*#%@”来输出
  void PrintInputImages();

  std::string dataTypeToString(DataType dataType) {
    switch (dataType) {
      case DataType::kFLOAT:
        return std::string("FP32 ");
      case DataType::kHALF:
        return std::string("FP16 ");
      case DataType::kINT8:
        return std::string("INT8 ");
      case DataType::kINT32:
        return std::string("INT32");
      case DataType::kBOOL:
        return std::string("BOOL ");
      default:
        return std::string("Unknown");
    }
  }
  size_t dataTypeToSize(DataType dataType) {
    switch ((int)dataType) {
      case int(DataType::kFLOAT):
        return 4;
      case int(DataType::kHALF):
        return 2;
      case int(DataType::kINT8):
        return 1;
      case int(DataType::kINT32):
        return 4;
      case int(DataType::kBOOL):
        return 1;
      default:
        return 4;
    }
  }
  bool ok_;

  // log
  Logger gLogger_;

  // engine
  ICudaEngine* engine_;

  std::vector<char> engine_string_;

  static const int INPUT_H = 28;

  static const int INPUT_W = 28;

  const int output_size_ = 10;

  uint8_t target_buffer_[INPUT_H * INPUT_W];

  std::string model_path_ = "./data/mnist.onnx";
  std::string plan_path_ = "./data/mnist.plan";
  std::string target_path_;
};

#endif  // CMAKE_SAMPLE_MNIST_
