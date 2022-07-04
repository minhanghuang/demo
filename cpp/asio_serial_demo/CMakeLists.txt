cmake_minimum_required(VERSION 3.5.1)
project(asio_serial)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)

include_directories(
  include
  ${Boost_INCLUDE_DIRS}
)

add_executable(${TARGET_NAME}_runner main.cc)

target_link_libraries(${TARGET_NAME}_runner
  pthread
)


