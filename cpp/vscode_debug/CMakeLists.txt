cmake_minimum_required(VERSION 3.5)
project(vscode_debug)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE DEBUG)

add_executable(vscode_debug main.cc)
