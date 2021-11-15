cmake_minimum_required(VERSION 3.17)
project(civetweb_demo)

set(TARGET_NAME ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
find_package(PkgConfig REQUIRED)
find_package(civetweb REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)
pkg_check_modules(NLOHMANNJSON REQUIRED nlohmann_json)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${NLOHMANNJSON_INCLUDE_DIRS}
)

link_directories (
    ${Boost_LIBRARY_DIRS}
    ${NLOHMANNJSON_LIBRARY_DIRS}
    /usr/local/lib
)

aux_source_directory(src ENGINE_SOURCE_DIRS)
aux_source_directory(include HTTP_ENGINE_SOURCE_DIRS)

add_library(${TARGET_NAME} SHARED
    ${HTTP_ENGINE_SOURCE_DIRS}
    ${ENGINE_SOURCE_DIRS}
)

target_link_libraries(${TARGET_NAME}
    libcivetweb-cpp.so
    libcivetweb.so
    ${Boost_LIBRARIES}
    ${NLOHMANNJSON_LIBRARIES}
)

add_executable(${TARGET_NAME}_runner main.cc)

target_link_libraries(${TARGET_NAME}_runner
    ${TARGET_NAME}
)