cmake_minimum_required(VERSION 3.19)
project(nlohmann_demo)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(Nlohmann_json REQUIRED nlohmann_json)

include_directories(
    ${Nlohmann_json_INCLUDE_DIRS}
)

link_directories (
    ${Nlohmann_json_LIBRARY_DIRS}
)

add_executable(${TARGET_NAME}_runner main.cc)

target_link_libraries(${TARGET_NAME}_runner
    ${Nlohmann_json_LIBRARIES}
)
