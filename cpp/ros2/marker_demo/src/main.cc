#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <utility>

#include <rclcpp/publisher.hpp>
#include <rclcpp/rclcpp.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("marker_node");

  // qos
  rclcpp::QoS qos(0);

  auto pub = node->create_publisher<visualization_msgs::msg::MarkerArray>(
      "/ros2/lane_markers", 1);

  // 创建一个MarkerArray消息
  auto marker_array = visualization_msgs::msg::MarkerArray();

  // 创建第一条车道线的Marker
  visualization_msgs::msg::Marker marker;
  marker.header.frame_id = "map";
  marker.header.stamp = node->now();
  marker.ns = "lane_markers";
  marker.id = 1;

  // LINE_STRIP: 一条连接所有点的线段
  // LINE_LIST: 每两个连续的点将会形成一条独立的线段
  marker.type = visualization_msgs::msg::Marker::LINE_STRIP;

  // ADD: 表示要添加一个新的 Marker
  marker.action = visualization_msgs::msg::Marker::ADD;

  marker.pose.orientation.w = 1.0;  // 四元素 设置为1.0,表示无旋转

  marker.scale.x = 0.01;  // x表示线段的宽度
  marker.color.r = 1.0;   // RGB
  marker.color.a = 1.0;   // 代表透明度

  for (int i = 0; i < 3; i++) {
    geometry_msgs::msg::Point point;
    point.set__x(i);
    point.set__y(i);
    point.set__z(0);
    marker.points.emplace_back(point);
  }

  marker_array.markers.emplace_back(marker);

  rclcpp::WallRate rate(5);
  while (rclcpp::ok()) {
    rclcpp::spin_some(node);
    pub->publish(marker_array);
    rate.sleep();
  }

  rclcpp::shutdown();
  return 0;
}
