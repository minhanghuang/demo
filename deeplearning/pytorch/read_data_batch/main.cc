#include <iostream>
#include <string>

#include <torch/torch.h>

int main(int argc, char* argv[]) {
  std::cout << "Hello, Torch C++ Load dataset" << std::endl;
  std::cout << "LibTorch Version: " << TORCH_VERSION << std::endl;

  if (2 != argc) {
    std::cout << "run: ./torch-read-dataset_runner dataset-files-path"
              << std::endl;
    // 数据集: https://www.cs.toronto.edu/\~kriz/cifar-10-binary.tar.gz
    return -1;
  }
  std::string file_path = argv[1];
  std::cout << "dataset path: " << file_path << std::endl;

  const int train_size = 50000;
  const int test_size = 10000;
  const int total_samples = 10000;  // 样本数量
  const int image_channel = 3;
  const int image_rows = 32;
  const int image_columns = 32;
  // 需要image_channel * image_rows * image_columns字节来存储图像数据
  // +1：这个额外的字节用于存储样本的标签
  const int bytes_per_row = image_channel * image_rows * image_columns + 1;

  const std::vector<std::string> train_databatch_files = {
      "data_batch_1.bin", "data_batch_2.bin", "data_batch_3.bin",
      "data_batch_4.bin", "data_batch_5.bin",
  };
  const std::vector<std::string> test_databatch_files = {"test_batch.bin"};

  std::vector<char> train_data_buffer;
  std::vector<char> test_data_buffer;
  train_data_buffer.reserve(train_databatch_files.size() * bytes_per_row *
                            total_samples);
  test_data_buffer.reserve(test_databatch_files.size() * bytes_per_row *
                           total_samples);

  for (const auto& file : train_databatch_files) {
    const auto path = file_path + file;
    std::cout << "train dataset file: " << path << std::endl;
    std::ifstream data(path, std::ios::binary);
    train_data_buffer.insert(train_data_buffer.end(),
                             std::istreambuf_iterator<char>(data), {});
  }
  for (const auto& file : test_databatch_files) {
    const auto path = file_path + file;
    std::cout << "test dataset file: " << path << std::endl;
    std::ifstream data(path, std::ios::binary);
    test_data_buffer.insert(test_data_buffer.end(),
                            std::istreambuf_iterator<char>(data), {});
  }

  const int train_num_samples = train_size;
  auto train_labels = torch::empty(train_num_samples, torch::kByte);
  auto train_images = torch::empty(
      {train_num_samples, image_channel, image_rows, image_columns},
      torch::kByte);
  for (uint32_t i = 0; i != train_num_samples; ++i) {
    uint32_t start_index = i * bytes_per_row;
    train_labels[i] = train_data_buffer[start_index];
    uint32_t image_start = start_index + 1;
    uint32_t image_end = image_start + 3 * 1024;
    std::copy(train_data_buffer.begin() + image_start,
              train_data_buffer.begin() + image_end,
              reinterpret_cast<char*>(train_images[i].data_ptr()));
  }

  const int test_num_samples = test_size;
  auto test_labels = torch::empty(test_num_samples, torch::kByte);
  auto test_images =
      torch::empty({test_num_samples, image_channel, image_rows, image_columns},
                   torch::kByte);
  for (uint32_t i = 0; i != test_num_samples; ++i) {
    uint32_t start_index = i * bytes_per_row;
    test_labels[i] = test_data_buffer[start_index];
    uint32_t image_start = start_index + 1;
    uint32_t image_end = image_start + 3 * 1024;
    std::copy(test_data_buffer.begin() + image_start,
              test_data_buffer.begin() + image_end,
              reinterpret_cast<char*>(test_images[i].data_ptr()));
  }

  std::pair<torch::Tensor, torch::Tensor> train_tensor = {
      train_images.to(torch::kFloat32).div_(255),
      train_labels.to(torch::kInt64)};

  std::pair<torch::Tensor, torch::Tensor> test_tensor = {
      test_images.to(torch::kFloat32).div_(255), test_labels.to(torch::kInt64)};

  // std::cout << "test labels: " << test_tensor.second << std::endl;

  return 0;
}
