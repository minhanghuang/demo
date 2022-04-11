#include <functional>
#include <iostream>
#include <memory>
#include <rclcpp/subscription.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>


class MyNode : public rclcpp::Node {
public:
  ~MyNode(){};
  MyNode(const rclcpp::NodeOptions& options) : Node("sub_parma_node", options) {
    sub1_ = this->create_subscription<std_msgs::msg::String>(
      "/topic1", 10, std::bind(&MyNode::callback1, this, std::placeholders::_1));
    this->declare_parameter("map_path","/opt/trunk30/share/trunk_hdmap_actor/data/HighWay/jj_20km.json");
  };

private:
  void callback1(const std_msgs::msg::String::SharedPtr msg) {
    std::string map_path;
    this->get_parameter("map_path",map_path);
    std::cout << " parma: " << map_path << std::endl;
    // std::cout << "sub: " << msg->data.c_str() << std::endl;
  }
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub1_;
};

int main(int argc, char *argv[]) {
  std::cout << "ros2 parma" << std::endl;
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MyNode>(rclcpp::NodeOptions()));
  rclcpp::shutdown();
  return 0;
}
