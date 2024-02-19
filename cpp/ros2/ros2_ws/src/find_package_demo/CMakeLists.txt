cmake_minimum_required(VERSION 3.5)
project(find_package_demo)

set(CMAKE_CXX_STANDARD 14)
set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(haha_demo REQUIRED)

include_directories(
  ${rclcpp_INCLUDE_DIRS}
  ${haha_demo_INCLUDE_DIRS}
)

add_executable(${TARGET_NAME} main.cc)

ament_target_dependencies(${TARGET_NAME}
  rclcpp
  haha_demo
)

install(TARGETS
  ${TARGET_NAME} 
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()

