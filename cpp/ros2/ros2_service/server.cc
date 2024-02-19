#include <iostream>
#include <rclcpp/rclcpp.hpp>

#include "hdmap/srv/local_map.hpp"

void handle_service(const std::shared_ptr<rmw_request_id_t> request_header,
                    const std::shared_ptr<hdmap::srv::LocalMap::Request> request,
                    const std::shared_ptr<hdmap::srv::LocalMap::Response> response) {
  std::cout << "request:" << request->id << std::endl;  
  response->set__status(200);
  (void)request_header;
}

int main(int argc, char *argv[]) {
  std::cout << "ros2 server" << std::endl;
  rclcpp::init(argc, argv);
  rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("minimal_server");
  auto server = node->create_service<hdmap::srv::LocalMap>("local_map", handle_service);
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}

