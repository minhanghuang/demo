#include <iostream>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

int main(int argc, char** argv) {
  std::cout << "Hello, Ros2 Pub!" << std::endl;
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("test_pub_node");
  auto chatter_pub = node->create_publisher<std_msgs::msg::String>("/topic", 1);
  rclcpp::WallRate r(5);

  std_msgs::msg::String msg;
  int i = 0;
  while (rclcpp::ok()) {
    msg.data = "data: " + std::to_string(i++);
    std::cout << "pub " << msg.data.c_str() << std::endl;
    chatter_pub->publish(msg);
    rclcpp::spin_some(node);
    r.sleep();
  }
  rclcpp::shutdown();
  return 0;
}
