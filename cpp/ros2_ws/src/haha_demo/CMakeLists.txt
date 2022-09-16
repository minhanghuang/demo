cmake_minimum_required(VERSION 3.5)
project(haha_demo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

add_library(${PROJECT_NAME} SHARED src/impl.cc)

target_include_directories(${TARGET_NAME}
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${TARGET_NAME}>
)

ament_export_targets(${TARGET_NAME})

install(
  TARGETS ${TARGET_NAME}
  EXPORT ${TARGET_NAME} 
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(
  DIRECTORY include/
  DESTINATION include/${TARGET_NAME}
)

ament_package()
