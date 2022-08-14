cmake_minimum_required(VERSION 3.5.1)
project(pcl_to_octomap_demo)

set(CMAKE_CXX_STANDARD 14)
set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(PCL REQUIRED)

include_directories(
  ${PCL_INCLUDE_DIRS}
)

link_libraries(
  ${PCL_LIBRARY_DIRS}
)

add_executable(${TARGET_NAME} main.cc)

ament_target_dependencies(${TARGET_NAME} 
  rclcpp
  std_msgs
  sensor_msgs
  PCL
)

install(TARGETS
  ${TARGET_NAME}
  DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
