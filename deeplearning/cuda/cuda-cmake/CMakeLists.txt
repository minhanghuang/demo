cmake_minimum_required(VERSION 3.8)

project(cuda_test)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_language(CUDA)

set(CUDA_SEPARABLE_COMPILATION ON)
set(CMAKE_CUDA_COMPILER "nvcc")

find_package(CUDA REQUIRED)

include_directories(
  ${CUDA_INCLUDE_DIRS}
)

link_directories(
  ${CUDA_LIBRARIES_DIRS}
)

add_executable(${TARGET_NAME} main.cu)

target_link_libraries(${TARGET_NAME}
  ${CUDA_LIBRARIES}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

