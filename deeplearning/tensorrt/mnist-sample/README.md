# Mnist frontend inference

## env

```shell
CUDA Version: 11.4
Driver Version: 470.82.01
TensorRT version: 8.5.4
```

## build

```shell
mkdir build && cd build
cmake ..
make -j$(nproc) && ./mnist-tensorrt ./data/0.pgm
```

