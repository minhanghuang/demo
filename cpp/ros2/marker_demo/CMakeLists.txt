cmake_minimum_required(VERSION 3.5)
project(marker_demo)

set(CMAKE_CXX_STANDARD 14)
set(TARGET_NAME ${PROJECT_NAME}_node)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)

add_executable(${TARGET_NAME} src/main.cc)

ament_target_dependencies(${TARGET_NAME}
  std_msgs
  visualization_msgs
  rclcpp
)

install(TARGETS
  ${TARGET_NAME}
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
