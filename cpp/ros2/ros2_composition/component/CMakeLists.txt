cmake_minimum_required(VERSION 3.5.1)
project(ros2_component)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread filesystem)

include_directories(
  ${Boost_INCLUDE_DIRS}
  ${rclcpp_INCLUDE_DIRS}
  ${rclcpp_components_INCLUDE_DIRS}
)

link_directories (
  ${Boost_LIBRARY_DIRS}
)

add_executable(${TARGET_NAME}_runner main.cc)

ament_target_dependencies(${TARGET_NAME}_runner
  rclcpp
  rclcpp_components 
)

target_link_libraries(${TARGET_NAME}_runner
  ${Boost_LIBRARIES}
)
