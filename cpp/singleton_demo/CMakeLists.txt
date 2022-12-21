cmake_minimum_required(VERSION 3.5.1)
project(singleton VERSION 0.0.0)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE) # Ubuntu 需要打开这两个配置
set(THREADS_PREFER_PTHREAD_FLAG TRUE) 

find_package(Threads REQUIRED)

add_executable(${TARGET_NAME}_runner main.cc)

target_link_libraries(${TARGET_NAME}_runner Threads::Threads)

