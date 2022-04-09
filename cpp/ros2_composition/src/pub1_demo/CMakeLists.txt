cmake_minimum_required(VERSION 3.5.1)
project(pub1_demo)

set(TARGET_NAME pub_component)
set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread filesystem)
find_package(ament_cmake REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${std_msgs_INCLUDE_DIRS}
    ${rclcpp_INCLUDE_DIRS}
    ${rclcpp_components_INCLUDE_DIRS}
)

link_directories(
  ${Boost_LIBRARY_DIRS}
)

add_library(${TARGET_NAME} SHARED
  src/pub.cc
)

target_link_libraries(${TARGET_NAME}
  ${Boost_LIBRARIES}
)

ament_target_dependencies(${TARGET_NAME}
  rclcpp
  rclcpp_components
  std_msgs
)

rclcpp_components_register_nodes(${TARGET_NAME} "Talker")

install(TARGETS
  ${TARGET_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

ament_package()


