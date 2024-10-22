#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>

struct __attribute__((packed)) Vector3 {
  float x;
  float y;
  float z;

  template <class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    ar& x;
    ar& y;
    ar& z;
  }
};

void PrintVectorChar(const std::vector<char>& data) {
  for (std::size_t i = 0; i < data.size(); ++i) {
    // 打印每个字节的十六进制值，宽度为2
    std::cout << std::hex << std::setw(2) << std::setfill('0') << "0x"
              << static_cast<int>(static_cast<unsigned char>(data[i])) << " ";
  }
}

int main(int argc, char* argv[]) {
  std::cout << "Hello, Boost Serialization" << std::endl;

  {
    std::cout << "序列化Vector3" << std::endl;
    Vector3 frame;

    // 赋值
    frame.x = 1.0f;
    frame.y = 2.0f;
    frame.z = 3.0f;

    // 序列化
    std::stringstream ss;
    boost::archive::binary_oarchive oa(ss);
    oa << frame;
    const std::string& str = ss.str();
    std::vector<char> buffer(str.begin(), str.end());
    PrintVectorChar(buffer);
    std::cout << "size: " << buffer.size() << std::endl;

    // check
    std::size_t offset = 0;
    float* frame_data = reinterpret_cast<float*>(&buffer[offset]);
    // assert(1.0 == frame_data[0]);
    // assert(2.0 == frame_data[1]);
    // assert(3.0 == frame_data[2]);
  }

  return 0;
}
