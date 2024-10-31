#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

#include <alpaca/alpaca.h>

struct MyStruct {   // 24B
  char a;           // 1B
  int b;            // 4B
  std::uint64_t c;  // 8B
  float d;          // 4B
  bool e;           // 1B
};

using Bytes = std::vector<std::uint8_t>;

template <typename T>
void Serialize(std::vector<std::uint8_t>& buffer, const T& value) {
  const std::uint8_t* data = reinterpret_cast<const std::uint8_t*>(&value);
  buffer.insert(buffer.end(), data, data + sizeof(T));
}

void PrintBytes(const Bytes& buffer, std::size_t length,
                const std::string& ns = "") {
  std::ostringstream oss;
  for (int i = 0; i < std::min<int>(length, buffer.size()); i++) {
    oss << "0x" << std::hex << std::setw(2) << std::setfill('0')
        << static_cast<int>(buffer[i]) << " ";
  }
  std::cout << ns << " buffer size:" << length << " data:" << oss.str()
            << std::endl;
}

int main(int argc, char* argv[]) {
  std::cout << "Hello, alpaca(https://github.com/p-ranav/alpaca)" << std::endl;

  MyStruct obj;
  obj.a = 'A';  // 0x41
  obj.b = 1;    // 0x01
  obj.c = 2;    // 0x02
  obj.d = 3.14f;
  obj.e = true;

  std::vector<std::uint8_t> buffer1;
  alpaca::serialize(obj, buffer1);
  PrintBytes(buffer1, buffer1.size(), "obj");

  std::vector<std::uint8_t> buffer2;
  Serialize(buffer2, obj);
  PrintBytes(buffer2, buffer2.size(), "obj");

  return 0;
}
