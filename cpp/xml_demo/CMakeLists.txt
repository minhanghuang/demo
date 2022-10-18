cmake_minimum_required(VERSION 3.5.1)
project(xml_demo VERSION 0.0.0)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(Tinyxml2 REQUIRED tinyxml2)

include_directories(
  ${Tinyxml2_INCLUDE_DIRS}
)

link_directories (
  ${Tinyxml2_LIBRARY_DIRS}
)

add_executable(${TARGET_NAME}_runner main.cc)

target_link_libraries(${TARGET_NAME}_runner
  ${Tinyxml2_LIBRARIES}
)

file(COPY
  "${PROJECT_SOURCE_DIR}/test.xml"
  DESTINATION "${PROJECT_BINARY_DIR}"
)
