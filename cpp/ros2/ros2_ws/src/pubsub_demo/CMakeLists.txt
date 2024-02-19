cmake_minimum_required(VERSION 3.5.1)
project(pubsub_demo)

set(CMAKE_CXX_STANDARD 14)
set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(pub src/pub.cc)
add_executable(sub src/sub.cc)

ament_target_dependencies(pub rclcpp std_msgs)
ament_target_dependencies(sub rclcpp std_msgs)

# 如果不安装，则无法通过ros2 run 找到启动节点
install(TARGETS
    pub
    sub
    DESTINATION lib/${PROJECT_NAME}
)

# 若不执行，则无法通过 ros2 run/launch 找到该package
ament_package()
