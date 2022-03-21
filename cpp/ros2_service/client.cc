#include <iostream>
#include <rclcpp/rclcpp.hpp>

#include "hdmap/srv/local_map.hpp"

int main(int argc, char *argv[]) {
  std::cout << "ros2 client" << std::endl;
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("minimal_client");
  auto client = node->create_client<hdmap::srv::LocalMap>("local_map");
  while (!client->wait_for_service(std::chrono::seconds(1))) {
    if (!rclcpp::ok()) {
      return 1;
    }
  } // 等待服务端启动 

  auto request = std::make_shared<hdmap::srv::LocalMap::Request>();
  request->set__id("10000");
  auto result_future = client->async_send_request(request);

  if (rclcpp::spin_until_future_complete(node, result_future) != rclcpp::FutureReturnCode::SUCCESS) {
    std::cout << "失败" << std::endl;
    return 1;
  }
  auto result = result_future.get();
  std::cout << "response:" << result->status << std::endl;
  rclcpp::shutdown();
  return 0;
}

