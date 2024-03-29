cmake_minimum_required(VERSION 3.5.1)

project(tensorrt-samples VERSION 0.0.0)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_language(CUDA)

set(CUDA_SEPARABLE_COMPILATION ON)
set(CMAKE_CUDA_COMPILER "nvcc")

find_package(CUDA 11.4 REQUIRED)
find_library(NVINFER NAMES nvinfer)
find_library(NVINFERPLUGIN NAMES nvinfer_plugin)
find_library(NVPARSERS NAMES nvparsers)
find_library(NVONNXPARSER NAMES nvonnxparser)

if(CUDA_FOUND AND NVINFER AND NVINFERPLUGIN AND NVPARSERS AND NVONNXPARSER)
  message("TensorRT available!")
  list(APPEND TENSORRT_LIBRARIES ${CUDA_LIBRARIES} nvinfer nvinfer_plugin nvparsers nvonnxparser)
  list(APPEND TENSORRT_INCLUDE_DIRS ${CUDA_INCLUDE_DIRS})
else()
  message("TensorRT NOT Available")
endif()

include_directories(
  ${CUDA_INCLUDE_DIRS}
)

add_subdirectory(mnist)
add_subdirectory(dynamic-reshape)

file(COPY data/
  DESTINATION ${CMAKE_BINARY_DIR}/data/
)

