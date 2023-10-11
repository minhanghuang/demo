#include <iostream>

#include <torch/torch.h>

int main(int argc, char* argv[]) {
  std::cout << "Hello, Torch" << std::endl;
  std::cout << "LibTorch Version: " << TORCH_VERSION << std::endl;

  return 0;
}
