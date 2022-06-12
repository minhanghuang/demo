cmake_minimum_required(VERSION 3.5.1)
project(project_name)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)
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
