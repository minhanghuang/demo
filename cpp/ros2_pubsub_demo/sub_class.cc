#include <functional>
#include <iostream>
#include <memory>
#include <rclcpp/subscription.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>


class MyNode : public rclcpp::Node {
public:
  ~MyNode(){};
  MyNode(const rclcpp::NodeOptions& options) : Node("sub_class_node", options) {
    sub1_ = this->create_subscription<std_msgs::msg::String>(
      "/topic", 10, std::bind(&MyNode::callback1, this, std::placeholders::_1));
  };

private:
  void callback1(const std_msgs::msg::String::SharedPtr msg) {
    std::cout << "sub c " << msg->data.c_str() << std::endl;
  }

  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub1_;
};

int main(int argc, char *argv[]) {
  std::cout << "ros2 node" << std::endl;
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MyNode>(rclcpp::NodeOptions()));
  rclcpp::shutdown();
  return 0;
}
