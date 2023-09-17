#include <iostream>

#include "dynamic-reshape.h"

/*
* Input:
  Input tensor has shape (1x1x28x28), with type of float32. One image at a time.
This model doesn't support mini-batch.
- Preprocessing:
  Images are resized into (28x28) in grayscale, with a black background and a
white foreground (the number should be in white). Color value is scaled to
[0.0, 1.0].
- Output:
  The likelihood of each number before softmax, with shape of (1x10).
*/
int main(int argc, char* argv[]) {
  std::cout << "Hello TensorRT" << std::endl;
  DynamicReshape trt;
  trt.Init(argc, argv);
  trt.Build();
  trt.Inference();
  return EXIT_SUCCESS;
}
