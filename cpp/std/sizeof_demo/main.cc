#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

struct Vector3 {
  float x;
  float y;
  float z;
};

// struct __attribute__((packed)) Frame { // 字节不对齐
struct Frame {             // 字节对齐
  std::uint8_t a;          // 1B
  std::uint8_t b;          // 1B
  std::array<float, 4> c;  // 4 * 4=16B
  Vector3 d;               // 12B
  // std::vector<int> e;
};

int main(int argc, char* argv[]) {
  std::cout << "Hello, sizeof" << std::endl;
  Frame frame;
  std::cout << "int size: " << sizeof(int) << std::endl;
  std::cout << "int32 size: " << sizeof(std::int32_t) << std::endl;
  std::cout << "float32 size: " << sizeof(float) << std::endl;
  std::cout << "float64 size: " << sizeof(double) << std::endl;
  std::cout << "Vector3 size: " << sizeof(Vector3) << std::endl;
  std::cout << "Frame size: " << sizeof(Frame) << std::endl;
  std::cout << "Frame size: " << sizeof(frame) << std::endl;
  assert(12 == sizeof(Vector3));
  assert(sizeof(Frame) == sizeof(frame));
  return 0;
}
