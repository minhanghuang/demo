
#include "pub.h"

using namespace std::chrono_literals;

Talker::Talker(const rclcpp::NodeOptions& options)
    : Node("talker", options), count_(0) {
  pub_ = create_publisher<std_msgs::msg::String>("/chatter", 10);
  timer_ = create_wall_timer(1s, std::bind(&Talker::on_timer, this));
}

void Talker::on_timer() {
  auto msg = std::make_unique<std_msgs::msg::String>();
  msg->data = "Hello World: " + std::to_string(++count_);
  std::flush(std::cout);
  pub_->publish(std::move(msg));
}

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(Talker)

