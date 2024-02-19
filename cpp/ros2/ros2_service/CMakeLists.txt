cmake_minimum_required(VERSION 3.5.1)
project(ros2_service)

set(TARGET_NAME PROJECT_NAME)
set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(hdmap REQUIRED)

include_directories(
  ${rclcpp_INCLUDE_DIRS}
  ${hdmap_INCLUDE_DIRS}
)

message(${rclcpp_INCLUDE_DIRS})
message(${hdmap_INCLUDE_DIRS})

add_executable(server server.cc)
add_executable(client client.cc)

ament_target_dependencies(server rclcpp std_msgs hdmap)
ament_target_dependencies(client rclcpp std_msgs hdmap)

