#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <utility>

#include <lifecycle_msgs/msg/transition.hpp>
#include <rclcpp/publisher.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_lifecycle/lifecycle_node.hpp>
#include <rclcpp_lifecycle/lifecycle_publisher.hpp>
#include <rcutils/logging_macros.h>
#include <std_msgs/msg/string.hpp>

using namespace std::chrono_literals;

class LifecycleTalker : public rclcpp_lifecycle::LifecycleNode {
 public:
  explicit LifecycleTalker(const std::string& node_name,
                           bool intra_process_comms = false)
      : rclcpp_lifecycle::LifecycleNode(
            node_name, rclcpp::NodeOptions().use_intra_process_comms(
                           intra_process_comms)) {}

  void Publish() {
    static size_t count = 0;
    auto msg = std::make_unique<std_msgs::msg::String>();
    msg->data = "Lifecycle HelloWorld #" + std::to_string(++count);

    if (!pub_->is_activated()) {
      RCLCPP_INFO(get_logger(),
                  "Lifecycle publisher is currently inactive. Messages are not "
                  "published.");
      return;
    } else {
      RCLCPP_INFO(get_logger(),
                  "Lifecycle publisher is active, Publishing: [%s]",
                  msg->data.c_str());
    }
    pub_->publish(std::move(msg));
  }

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_configure(const rclcpp_lifecycle::State&) {
    pub_ =
        this->create_publisher<std_msgs::msg::String>("lifecycle_chatter", 10);
    timer_ =
        this->create_wall_timer(1s, std::bind(&LifecycleTalker::Publish, this));
    RCLCPP_INFO(get_logger(), "on_configure() is called.");
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_activate(const rclcpp_lifecycle::State&) {
    pub_->on_activate();
    RCUTILS_LOG_INFO_NAMED(get_name(), "on_activate() is called.");
    std::this_thread::sleep_for(2s);
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_deactivate(const rclcpp_lifecycle::State&) {
    pub_->on_deactivate();
    RCUTILS_LOG_INFO_NAMED(get_name(), "on_deactivate() is called.");
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_cleanup(const rclcpp_lifecycle::State&) {
    timer_.reset();
    pub_.reset();
    RCUTILS_LOG_INFO_NAMED(get_name(), "on_cleanup() is called.");
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_shutdown(const rclcpp_lifecycle::State& state) {
    timer_.reset();
    pub_.reset();
    RCUTILS_LOG_INFO_NAMED(get_name(), "on shutdown is called from state %s.",
                           state.label().c_str());
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

 private:
  std::shared_ptr<rclcpp_lifecycle::LifecyclePublisher<std_msgs::msg::String>>
      pub_;
  std::shared_ptr<rclcpp::TimerBase> timer_;
};

int main(int argc, char* argv[]) {
  setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  rclcpp::init(argc, argv);
  rclcpp::executors::SingleThreadedExecutor exe;
  std::shared_ptr<LifecycleTalker> lc_node =
      std::make_shared<LifecycleTalker>("lifecycle_demo_node");
  exe.add_node(lc_node->get_node_base_interface());
  exe.spin();
  rclcpp::shutdown();
  return 0;
}
