#include <functional>
#include <iostream>
#include <memory>
#include <unistd.h>
#include <rclcpp/subscription.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/node_options.hpp>
#include <std_msgs/msg/string.hpp>



class MyNode : public rclcpp::Node {
public:
  ~MyNode(){};
  MyNode(const rclcpp::NodeOptions& options) : Node("sub_node", options) {
    // MutuallyExclusive: 互斥，这个组别中每时刻只允许1个线程，一个callback在执行时，其他callback只能等待
    // Reentrant: 一个callback在执行时，其他callback可开启新的线程
    // Ros2 中每个node默认都有一个group, 默认MutuallyExclusive类型, 几遍使用多线程的executor, 这个组的callback也是互斥
    group_sub1_ = this->create_callback_group(rclcpp::callback_group::CallbackGroupType::MutuallyExclusive);
    group_sub2_ = this->create_callback_group(rclcpp::callback_group::CallbackGroupType::MutuallyExclusive);

    auto sub1_opt = rclcpp::SubscriptionOptions();
    sub1_opt.callback_group = group_sub1_;
    auto sub2_opt = rclcpp::SubscriptionOptions();
    sub2_opt.callback_group = group_sub2_;

    sub1_ = this->create_subscription<std_msgs::msg::String>(
      "/topic1", 10, std::bind(&MyNode::callback1, this, std::placeholders::_1), sub1_opt);
    sub2_ = this->create_subscription<std_msgs::msg::String>(
      "/topic2", 100, std::bind(&MyNode::callback2, this, std::placeholders::_1), sub2_opt);
    sub3_ = this->create_subscription<std_msgs::msg::String>(
      "/topic3", 100, std::bind(&MyNode::callback3, this, std::placeholders::_1), sub2_opt);
};

private:
  void callback1(const std_msgs::msg::String::SharedPtr msg) {
    // std::cout << "sub 1 " << msg->data.c_str() << std::endl; 
    usleep(1000);
  }
  void callback2(const std_msgs::msg::String::SharedPtr msg) const {
    std::cout << "sub 2 " << msg->data.c_str() << std::endl; 
    sleep(1);
  }
  void callback3(const std_msgs::msg::String::SharedPtr msg) const {
    std::cout << "sub 3 " << msg->data.c_str() << std::endl; 
  }

  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub1_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub2_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub3_;
  rclcpp::callback_group::CallbackGroup::SharedPtr group_sub1_;
  rclcpp::callback_group::CallbackGroup::SharedPtr group_sub2_;
};

int main(int argc, char *argv[]) {
  std::cout << "ros2 multithreaded node" << std::endl;
  rclcpp::init(argc, argv);

  // rclcpp::spin(std::make_shared<MyNode>(rclcpp::NodeOptions()));
  // rclcpp::shutdown();

  rclcpp::executors::MultiThreadedExecutor executor(rclcpp::executor::ExecutorArgs(),5,true);
  auto node = std::make_shared<MyNode>(rclcpp::NodeOptions());
  executor.add_node(node);
  executor.spin();
  rclcpp::shutdown();

  return 0;
}
