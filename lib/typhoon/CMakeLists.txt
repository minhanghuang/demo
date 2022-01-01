cmake_minimum_required(VERSION 3.19)
project(typhoon)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
find_package(civetweb)
find_package(Boost REQUIRED COMPONENTS system thread)
pkg_check_modules(NLOHMANNJSON REQUIRED nlohmann_json)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${NLOHMANNJSON_INCLUDE_DIRS}
    ${civetweb_INCLUDE_DIR}
)

link_directories (
    /usr/local/lib
    ${Boost_LIBRARY_DIRS}
    ${NLOHMANNJSON_LIBRARY_DIRS}
)

aux_source_directory(src TYPHOON_SOURCE_DIRS)

add_library(${TARGET_NAME} SHARED
    ${TYPHOON_SOURCE_DIRS}
)

target_link_libraries(${TARGET_NAME}
    libcivetweb-cpp.so
    libcivetweb.so
    ${Boost_LIBRARIES}
    ${NLOHMANNJSON_LIBRARIES}
)



