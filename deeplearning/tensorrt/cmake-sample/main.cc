#include <iostream>

#include "src/node.h"

int main(int argc, char* argv[]) {
  std::cout << "Hello TensorRT" << std::endl;
  Node node(argc, argv);
  node.Init();
  node.Build();
  // node.Inference();
  // node.Destroy();
  return EXIT_SUCCESS;
}
