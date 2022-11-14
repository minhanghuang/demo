cmake_minimum_required(VERSION 3.5.1)
project(boost_demo VERSION 0.0.0)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Boost REQUIRED)

include_directories(
  ${Boost_INCLUDE_DIRS}
)

link_directories (
  ${Boost_LIBRARY_DIRS}
)

add_executable(${TARGET_NAME}_runner main.cc)

target_link_libraries(${TARGET_NAME}_runner
  ${Boost_LIBRARIES}
)
