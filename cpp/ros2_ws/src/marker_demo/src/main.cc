#include <cstddef>
#include <geometry_msgs/msg/detail/point__struct.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/time.hpp>
#include <std_msgs/msg/string.hpp>
#include <visualization_msgs/msg/detail/marker__struct.hpp>
#include <visualization_msgs/msg/detail/marker_array__struct.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

int main(int argc, char **argv) {
  std::cout << "Hello, ROS2 Marker!" << std::endl;
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("marker_node");
  auto pub = node->create_publisher<visualization_msgs::msg::MarkerArray>(
      "/marker", 1);
  rclcpp::WallRate r(1);

  visualization_msgs::msg::MarkerArray marker_array;
  visualization_msgs::msg::Marker marker;
  marker_array.markers.clear();
  marker.header.frame_id = "map";
  marker.color.r = 1.0;
  marker.color.g = .0;
  marker.color.b = .0;
  marker.color.a = 1;
  marker.type = visualization_msgs::msg::Marker::CUBE;
  marker.action = visualization_msgs::msg::Marker::ADD;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  for (size_t i = 0; i < 10; i++) {
    geometry_msgs::msg::Point point;
    marker.id = i;
    marker.pose.position.x = i;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.scale.x = 1;
    marker.scale.y = 1;
    marker.scale.z = 1;
    marker_array.markers.emplace_back(marker);
  }

  while (rclcpp::ok()) {
    pub->publish(marker_array);
    rclcpp::spin_some(node);
    r.sleep();
  }

  rclcpp::shutdown();
  return 0;
}
