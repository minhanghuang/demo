cmake_minimum_required(VERSION 3.5.1)
project(octomap_demo)

set(CMAKE_CXX_STANDARD 14)
set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(octomap_msgs REQUIRED)
find_package(octomap REQUIRED)

add_executable(${TARGET_NAME} main.cc)

ament_target_dependencies(${TARGET_NAME} 
  std_msgs
  octomap_msgs 
  octomap 
  rclcpp
)

install(TARGETS
  ${TARGET_NAME}
  DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY
  launch
  param 
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
