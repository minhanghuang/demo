#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

using namespace std::chrono_literals;


class MyNode : public rclcpp::Node {
 public:
  MyNode() : Node("pub_class_node"), count_(0) {
    pub_ = this->create_publisher<std_msgs::msg::String>("/topic", 10);
    timer_ = this->create_wall_timer(
        500ms, std::bind(&MyNode::timer_callback, this));
  }

 private:
  void timer_callback() {
    auto msg = std_msgs::msg::String();
    msg.data = "Hello, world! " + std::to_string(count_++);
    std::cout << "pub " << msg.data.c_str() << std::endl;
    pub_->publish(msg);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
  size_t count_;
};

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MyNode>());
  rclcpp::shutdown();
  return 0;
}
