cmake_minimum_required(VERSION 3.5.1)
project(ros2_pubsub_demo)

set(CMAKE_CXX_STANDARD 14)
set(TARGET_NAME ${PROJECT_NAME})

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(
    ${std_msgs_INCLUDE_DIRS}
    ${rclcpp_INCLUDE_DIRS}
)

add_executable(pub pub.cc)
add_executable(sub sub.cc)

ament_target_dependencies(pub rclcpp std_msgs)
ament_target_dependencies(sub rclcpp std_msgs)
