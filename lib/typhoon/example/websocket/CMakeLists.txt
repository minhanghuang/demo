cmake_minimum_required(VERSION 3.5)
project(typhoon_ws_demo)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)

include_directories(../../src)


add_executable(${TARGET_NAME}_runner main.cc)

target_link_libraries(${TARGET_NAME}_runner
    typhoon
)
