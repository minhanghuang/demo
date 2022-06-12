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

link_directories(
  ${Boost_LIBRARY_DIRS}
)

add_library(${TARGET_NAME} SHARED
  src/parser.cc
  src/serial.cc
)

target_link_libraries(${TARGET_NAME}
  pthread
  # ${Boost_LIBRARIES}
)

add_executable(${TARGET_NAME}_runner main.cc)
add_executable(${TARGET_NAME}_xxx main_s.cc)

target_link_libraries(${TARGET_NAME}_runner
  ${TARGET_NAME}
)

target_link_libraries(${TARGET_NAME}_xxx
  ${TARGET_NAME}
)
