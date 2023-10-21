cmake_minimum_required(VERSION 3.5.1)
project(opencv-demo VERSION 0.0.0)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)

include_directories(
  ${OpenCV_INCLUDE_DIRS}
)

message("OpenCV include path:${OpenCV_INCLUDE_DIRS}")
message("OpenCV libs:${OpenCV_LIBRARIES}")
message("OpenCV libs:${OpenCV_LIBS}")

add_executable(${TARGET_NAME}_runner main.cc)

target_link_libraries(${TARGET_NAME}_runner
  ${OpenCV_LIBRARIES}
)

file(COPY "images"
  DESTINATION ${CMAKE_BINARY_DIR}
)
