cmake_minimum_required(VERSION 3.19)
project(curl_demo)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread filesystem)
pkg_check_modules(Curl REQUIRED libcurl)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${Curl_INCLUDE_DIRS}
)

link_directories (
    ${Boost_LIBRARY_DIRS}
    ${Curl_LIBRARY_DIRS}
)

add_executable(${TARGET_NAME}_runner main.cc)
add_executable(http_file_runner http_file.cc)

target_link_libraries(${TARGET_NAME}_runner
    ${Boost_LIBRARIES}
    ${Curl_LIBRARIES}
)
target_link_libraries(http_file_runner
    ${Boost_LIBRARIES}
    ${Curl_LIBRARIES}
)