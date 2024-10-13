#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

// 12B
struct __attribute__((packed)) Vector3 {
  float x;
  float y;
  float z;
};

struct __attribute__((packed)) Frame {  // POD
  std::uint8_t a;                       // 1B
  std::uint8_t b;                       // 1B
  std::array<float, 4> c;               // 4 * 4=16B
  Vector3 d;                            // 12B
};

struct __attribute__((packed)) Frame2 {
  std::array<float, 4> a;  // 16B
  std::uint16_t b_size;    // 2B
  std::vector<Vector3> b;
};

template <typename T>
void Serialize(std::vector<char>& buffer, const T& value) {
  const char* data = reinterpret_cast<const char*>(&value);
  buffer.insert(buffer.end(), data, data + sizeof(T));
}

template <typename T>
void Deserialize(const std::vector<char>& buffer, size_t& offset, T& value) {
  // 从 buffer 中提取 T 类型的值
  std::memcpy(&value, buffer.data() + offset, sizeof(T));
  offset += sizeof(T);  // 更新 offset
}

template <typename T, size_t N>
void Deserialize(const std::vector<char>& buffer, size_t& offset,
                 std::array<T, N>& arr) {
  for (size_t i = 0; i < N; ++i) {
    Deserialize(buffer, offset, arr[i]);  // 递归反序列化每个元素
  }
}

template <typename T>
void Deserialize(const std::vector<char>& buffer, size_t& offset,
                 std::vector<T>& vec, std::size_t size) {
  vec.resize(size);  // 根据传入的大小调整 vector 大小
  for (size_t i = 0; i < size; ++i) {
    Deserialize(buffer, offset, vec[i]);  // 递归反序列化每个元素
  }
}

int main(int argc, char* argv[]) {
  std::cout << "Hello, byte" << std::endl;
  {
    std::cout << "赋值" << std::endl;
    Frame frame;
    // std::vector<char> buffer; // err
    std::vector<char> buffer(sizeof(Frame));
    frame.a = 1;
    frame.b = 2;
    frame.c[0] = 10;
    frame.c[1] = 20;
    frame.c[2] = 30;
    frame.c[3] = 40;
    frame.d.x = 100;
    frame.d.y = 200;
    frame.d.z = 300;
    std::memcpy(buffer.data(), &frame, sizeof(frame));
  }
  {
    std::cout << "序列化" << std::endl;
    Frame frame;
    frame.a = 1;
    frame.b = 2;
    frame.c[0] = 10;
    frame.c[1] = 20;
    frame.c[2] = 30;
    frame.c[3] = 40;
    frame.d.x = 100;
    frame.d.y = 200;
    frame.d.z = 300;
    const std::size_t frame_size = sizeof(Frame);
    std::vector<char> buffer(frame_size);
    std::memcpy(buffer.data(), &frame, frame_size);

    std::size_t offset = 0;

    assert(0x01 == buffer[offset]);
    offset += sizeof(frame.a);

    assert(0x02 == buffer[offset]);
    offset += sizeof(frame.b);

    float* c_data = reinterpret_cast<float*>(&buffer[offset]);
    assert(10 == c_data[0]);
    assert(20 == c_data[1]);
    assert(30 == c_data[2]);
    assert(40 == c_data[3]);
    offset += sizeof(frame.c);

    float* d_data = reinterpret_cast<float*>(&buffer[offset]);
    assert(100 == d_data[0]);
    assert(200 == d_data[1]);
    assert(300 == d_data[2]);
    offset += sizeof(frame.d);
  }

  {
    std::cout << "序列化2" << std::endl;
    Frame2 frame;
    frame.a[0] = 10;
    frame.a[1] = 20;
    frame.a[2] = 30;
    frame.a[3] = 40;
    frame.b_size = 5;
    for (int i = 0; i < frame.b_size; i++) {
      Vector3 vector3;
      vector3.x = i + 1;
      vector3.y = i + 2;
      vector3.z = i + 3;
      frame.b.emplace_back(vector3);
    }

    std::vector<char> buffer;

    // 1. 序列化 std::array<float, 4> a
    buffer.resize(sizeof(frame.a));
    std::memcpy(buffer.data(), frame.a.data(), sizeof(frame.a));

    // 2. 序列化 b_size
    std::uint16_t b_size = frame.b_size;
    buffer.insert(buffer.end(), reinterpret_cast<char*>(&b_size),
                  reinterpret_cast<char*>(&b_size) + sizeof(b_size));

    // 3. 序列化 std::vector<Vector3> b 的内容
    if (!frame.b.empty()) {
      size_t b_data_size = frame.b_size * sizeof(Vector3);
      buffer.resize(buffer.size() + b_data_size);
      std::memcpy(buffer.data() + sizeof(frame.a) + sizeof(frame.b_size),
                  frame.b.data(), b_data_size);
    }

    assert(buffer.size() == sizeof(frame.a) + sizeof(frame.b_size) +
                                frame.b_size * sizeof(frame.b[0]));

    std::size_t offset = 0;

    float* a_data = reinterpret_cast<float*>(&buffer[offset]);
    assert(10 == a_data[0]);
    assert(20 == a_data[1]);
    assert(30 == a_data[2]);
    assert(40 == a_data[3]);
    offset += sizeof(frame.a);

    assert(5 == buffer[offset]);
    offset += sizeof(frame.b_size);

    for (int i = 0; i < frame.b_size; i++) {
      float* data = reinterpret_cast<float*>(&buffer[offset]);
      assert(i + 1 == data[0]);
      assert(i + 2 == data[1]);
      assert(i + 3 == data[2]);
      offset += sizeof(Vector3);
    }
  }

  {
    std::cout << "序列化3" << std::endl;
    Frame2 frame;
    frame.a[0] = 10;
    frame.a[1] = 20;
    frame.a[2] = 30;
    frame.a[3] = 40;
    frame.b_size = 5;
    for (int i = 0; i < frame.b_size; i++) {
      Vector3 vector3;
      vector3.x = i + 1;
      vector3.y = i + 2;
      vector3.z = i + 3;
      frame.b.emplace_back(vector3);
    }

    std::vector<char> buffer;
    Serialize(buffer, frame.a);
    Serialize(buffer, frame.b_size);
    for (const auto& item : frame.b) {
      Serialize(buffer, item.x);
      Serialize(buffer, item.y);
      Serialize(buffer, item.z);
    }

    // 16B + 2B + 5 * 12B = 84B
    assert(buffer.size() == sizeof(frame.a) + sizeof(frame.b_size) +
                                frame.b_size * sizeof(frame.b[0]));

    std::size_t offset = 0;
    float* a_data = reinterpret_cast<float*>(&buffer[offset]);
    assert(10 == a_data[0]);
    assert(20 == a_data[1]);
    assert(30 == a_data[2]);
    assert(40 == a_data[3]);
    offset += sizeof(frame.a);

    assert(5 == buffer[offset]);
    offset += sizeof(frame.b_size);

    for (int i = 0; i < frame.b_size; i++) {
      float* data = reinterpret_cast<float*>(&buffer[offset]);
      assert(i + 1 == data[0]);
      assert(i + 2 == data[1]);
      assert(i + 3 == data[2]);
      offset += sizeof(Vector3);
    }
  }

  {
    std::cout << "反序列化" << std::endl;
    Frame frame;
    std::vector<char> buffer;

    // 1. 序列化 a 和 b
    buffer.push_back(static_cast<char>(1));  // a
    buffer.push_back(static_cast<char>(2));  // b

    // 2. 序列化 c (std::array<float, 4>)
    for (int i = 0; i < 4; i++) {
      float value = i + 0.5f;  // 假设值为 0.5, 1.5, 2.5, 3.5
      const char* c_ptr = reinterpret_cast<const char*>(&value);
      buffer.insert(buffer.end(), c_ptr, c_ptr + sizeof(float));
    }

    // 3. 序列化 d (Vector3)
    Vector3 d = {100.0f, 200.0f,
                 300.0f};  // 假设 d.x = 100, d.y = 200, d.z = 300
    const char* d_ptr = reinterpret_cast<const char*>(&d);
    buffer.insert(buffer.end(), d_ptr, d_ptr + sizeof(Vector3));

    // 反序列化
    std::memcpy(&frame, buffer.data(), sizeof(Frame));

    assert(1 == frame.a);
    assert(2 == frame.b);
    assert(0.5f == frame.c[0]);
    assert(1.5f == frame.c[1]);
    assert(2.5f == frame.c[2]);
    assert(3.5f == frame.c[3]);
    assert(100.0f == frame.d.x);
    assert(200.0f == frame.d.y);
    assert(300.0f == frame.d.z);
  }

  {
    std::cout << "反序列化2" << std::endl;
    Frame frame;
    std::vector<char> buffer;

    // 1. 序列化 a 和 b
    buffer.push_back(static_cast<char>(1));  // a
    buffer.push_back(static_cast<char>(2));  // b

    // 2. 序列化 c (std::array<float, 4>)
    for (int i = 0; i < 4; i++) {
      float value = i + 0.5f;  // 假设值为 0.5, 1.5, 2.5, 3.5
      const char* c_ptr = reinterpret_cast<const char*>(&value);
      buffer.insert(buffer.end(), c_ptr, c_ptr + sizeof(float));
    }

    // 3. 序列化 d (Vector3)
    Vector3 d = {100.0f, 200.0f,
                 300.0f};  // 假设 d.x = 100, d.y = 200, d.z = 300
    const char* d_ptr = reinterpret_cast<const char*>(&d);
    buffer.insert(buffer.end(), d_ptr, d_ptr + sizeof(Vector3));

    // 反序列化
    std::size_t offset = 0;
    Deserialize(buffer, offset, frame);

    assert(1 == frame.a);
    assert(2 == frame.b);
    assert(0.5f == frame.c[0]);
    assert(1.5f == frame.c[1]);
    assert(2.5f == frame.c[2]);
    assert(3.5f == frame.c[3]);
    assert(100.0f == frame.d.x);
    assert(200.0f == frame.d.y);
    assert(300.0f == frame.d.z);
  }

  {
    std::cout << "反序列化3" << std::endl;
    Frame2 frame;
    std::vector<char> buffer;

    for (int i = 0; i < 4; i++) {
      float value = i + 0.5f;  // 假设值为 0.5, 1.5, 2.5, 3.5
      const char* a_ptr = reinterpret_cast<const char*>(&value);
      buffer.insert(buffer.end(), a_ptr, a_ptr + sizeof(float));
    }

    buffer.push_back(static_cast<char>(5));  // b_size
    buffer.push_back(0);  // 注意  这里被序列化为两个字节

    for (int i = 0; i < 5; i++) {
      Vector3 vector3;
      vector3.x = i + 1;
      vector3.y = i + 2;
      vector3.z = i + 3;
      const char* vector3_ptr = reinterpret_cast<const char*>(&vector3);
      buffer.insert(buffer.end(), vector3_ptr, vector3_ptr + sizeof(Vector3));
    }

    std::size_t offset = 0;

    // 1. 反序列化 std::array<float, 4>
    std::memcpy(frame.a.data(), buffer.data() + offset, sizeof(frame.a));
    offset += sizeof(frame.a);

    // 2. 反序列化 std::uint16_t b_size
    std::memcpy(&frame.b_size, buffer.data() + offset, sizeof(frame.b_size));
    offset += sizeof(frame.b_size);

    // 3. 反序列化 std::vector<Vector3>
    frame.b.resize(frame.b_size);  // 调整 b 的大小以存储正确数量的 Vector3
    for (int i = 0; i < frame.b_size; ++i) {
      std::memcpy(&frame.b[i], buffer.data() + offset, sizeof(Vector3));
      offset += sizeof(Vector3);
    }

    assert(0.5f == frame.a[0]);
    assert(1.5f == frame.a[1]);
    assert(2.5f == frame.a[2]);
    assert(3.5f == frame.a[3]);
    assert(5 == frame.b_size);
    for (int i = 0; i < frame.b_size; i++) {
      // std::cout << frame.b[i].x << std::endl;
      // std::cout << frame.b[i].y << std::endl;
      // std::cout << frame.b[i].z << std::endl;
      assert(i + 1 == frame.b[i].x);
      assert(i + 2 == frame.b[i].y);
      assert(i + 3 == frame.b[i].z);
    }
  }

  {
    std::cout << "反序列化4" << std::endl;
    Frame2 frame;
    std::vector<char> buffer;

    for (int i = 0; i < 4; i++) {
      float value = i + 0.5f;  // 假设值为 0.5, 1.5, 2.5, 3.5
      const char* a_ptr = reinterpret_cast<const char*>(&value);
      buffer.insert(buffer.end(), a_ptr, a_ptr + sizeof(float));
    }

    buffer.push_back(static_cast<char>(5));  // b_size
    buffer.push_back(0);  // 注意  这里被序列化为两个字节

    for (int i = 0; i < 5; i++) {
      Vector3 vector3;
      vector3.x = i + 1;
      vector3.y = i + 2;
      vector3.z = i + 3;
      const char* vector3_ptr = reinterpret_cast<const char*>(&vector3);
      buffer.insert(buffer.end(), vector3_ptr, vector3_ptr + sizeof(Vector3));
    }

    std::size_t offset = 0;
    Deserialize(buffer, offset, frame.a);
    Deserialize(buffer, offset, frame.b_size);
    frame.b.resize(frame.b_size);  // 设置大小
    for (auto& ele : frame.b) {
      Deserialize(buffer, offset, ele);
    }

    assert(0.5f == frame.a[0]);
    assert(1.5f == frame.a[1]);
    assert(2.5f == frame.a[2]);
    assert(3.5f == frame.a[3]);
    assert(5 == frame.b_size);
    for (int i = 0; i < frame.b_size; i++) {
      // std::cout << frame.b[i].x << std::endl;
      // std::cout << frame.b[i].y << std::endl;
      // std::cout << frame.b[i].z << std::endl;
      assert(i + 1 == frame.b[i].x);
      assert(i + 2 == frame.b[i].y);
      assert(i + 3 == frame.b[i].z);
    }
  }

  return 0;
}
