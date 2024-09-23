#include <array>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

// size: 4+20+4=28
struct Header {
  int id;
  char version[20];
  float stamp;

  int Size() const { return sizeof(id) + sizeof(version) + sizeof(stamp); }

  bool Serialize(std::vector<char>* buffer) {
    size_t offset = 0;
    // 计算总需要的缓冲区大小并预留空间以提高效率
    buffer->resize(Size());

    // 序列化 id
    std::memcpy(buffer->data() + offset, &id, sizeof(id));
    offset += sizeof(id);

    // 序列化 version
    std::memcpy(buffer->data() + offset, &version, sizeof(version));
    offset += sizeof(version);

    // 序列化 stamp
    std::memcpy(buffer->data() + offset, &stamp, sizeof(stamp));
    return true;
  }

  bool Deserialize(const std::vector<char>& buffer) {
    size_t offset = 0;
    // 反序列化 id
    std::memcpy(&id, buffer.data() + offset, sizeof(id));
    offset += sizeof(id);

    // 反序列化 version
    std::memcpy(version, buffer.data() + offset, sizeof(version));
    offset += sizeof(version);

    // 反序列化 stamp
    std::memcpy(&stamp, buffer.data() + offset, sizeof(stamp));
    return true;
  }
};

// size: 4+4+n*4+8*5
struct Data {
  int value;
  int vector_size;
  std::vector<float> vector_value;
  std::array<double, 5> array_value;

  int Size() const {
    return sizeof(value) + sizeof(vector_size) + vector_size * sizeof(float) +
           sizeof(double) * 5;
  }

  bool Serialize(std::vector<char>* buffer) {
    size_t offset = 0;
    buffer->resize(Size());

    // 序列化 value
    std::memcpy(buffer->data() + offset, &value, sizeof(value));
    offset += sizeof(value);

    // 序列化 array_size
    std::memcpy(buffer->data() + offset, &vector_size, sizeof(vector_size));
    offset += sizeof(vector_size);

    // 序列化vector
    std::memcpy(buffer->data() + offset, vector_value.data(),
                vector_size * sizeof(float));
    offset += vector_size * sizeof(float);

    // 序列化array
    std::memcpy(buffer->data() + offset, array_value.data(),
                sizeof(double) * 5);
    return true;
  }

  bool Deserialize(const std::vector<char>& buffer) {
    size_t offset = 0;
    std::memcpy(&value, buffer.data() + offset, sizeof(value));
    offset += sizeof(value);

    std::memcpy(&vector_size, buffer.data() + offset, sizeof(vector_size));
    offset += sizeof(vector_size);

    vector_value.resize(vector_size);
    std::memcpy(vector_value.data(), buffer.data() + offset,
                vector_size * sizeof(float));
    offset += vector_size * sizeof(float);

    std::memcpy(array_value.data(), buffer.data() + offset, sizeof(double) * 5);
    return true;
  }
};

struct Frame {
  Header header;
  Data data;

  int Size() const { return header.Size() + data.Size(); }

  bool Serialize(std::vector<char>* buffer) {
    // 序列化 Header
    std::vector<char> header_buffer;
    header.Serialize(&header_buffer);
    buffer->insert(buffer->end(), header_buffer.begin(), header_buffer.end());

    // 序列化 Data
    std::vector<char> data_buffer;
    data.Serialize(&data_buffer);
    buffer->insert(buffer->end(), data_buffer.begin(), data_buffer.end());
    return true;
  }

  bool Deserialize(const std::vector<char>& buffer) {
    size_t offset = 0;

    // 反序列化 Header
    std::vector<char> header_buffer(buffer.begin(), buffer.end());
    header.Deserialize(header_buffer);
    offset += header.Size();

    // 反序列化 Data
    std::vector<char> data_buffer(buffer.begin() + offset, buffer.end());
    data.Deserialize(data_buffer);
    return true;
  }
};
