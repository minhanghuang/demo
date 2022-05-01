cmake_minimum_required(VERSION 3.5)
project(typhoon_demo)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
pkg_check_modules(Nlohmann_json REQUIRED nlohmann_json)
pkg_check_modules(Typhoon typhoon)

include_directories(
    /usr/local/include
    ${Typhoon_INCLUDE_DIRS}
    ${Nlohmann_json_INCLUDE_DIRS}
)

link_directories (
    /usr/local/lib
    ${Typhoon_LIBRARY_DIRS}
    ${Nlohmann_json_LIBRARY_DIRS}
)

add_executable(${TARGET_NAME}_runner main.cc)

target_link_libraries(${TARGET_NAME}_runner
    ${Nlohmann_json_LIBRARIES}
    ${Typhoon_LIBRARIES}
)