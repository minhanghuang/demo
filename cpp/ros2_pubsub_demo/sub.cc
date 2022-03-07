#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

void callback(const std_msgs::msg::String::SharedPtr msg) {
    std::cout << "sub " << msg->data.c_str() << std::endl;
}


int main(int argc, char **argv) {
    std::cout << "Hello, ROS2 Sub!" << std::endl;
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("sub_node");
    auto sub = node->create_subscription<std_msgs::msg::String>("/pub", 1, callback);
    rclcpp::spin(node);
    return 0;
}
