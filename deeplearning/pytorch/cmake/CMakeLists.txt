cmake_minimum_required(VERSION 3.5.1)

project(torch-cmake VERSION 0.0.0)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
find_package(Torch REQUIRED)

include_directories(
  ${TORCH_INCLUDE_DIRS}
)

add_executable(${TARGET_NAME}_runner main.cc)

target_link_libraries(${TARGET_NAME}_runner
  ${TORCH_LIBRARIES}
)
