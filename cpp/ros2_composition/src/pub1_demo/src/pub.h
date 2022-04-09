#include <iostream>
#include <chrono>
#include <iostream>
#include <memory>
#include <utility>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include "visibility_control.h"


class Talker : public rclcpp::Node {
public:
  COMPOSITION_PUBLIC
  explicit Talker(const rclcpp::NodeOptions & options);

protected:
  void on_timer();

private:
  size_t count_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;

};

