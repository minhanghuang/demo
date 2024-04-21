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
  auto node = rclcpp::Node::make_shared("marker_demo_node");

  rclcpp::QoS qos(0);

  // https://docs.ros2.org/foxy/api/visualization_msgs/msg/MarkerArray.html
  auto pub = node->create_publisher<visualization_msgs::msg::MarkerArray>(
      "/ros2/demo/lane_markers", 1);

  auto marker_array = visualization_msgs::msg::MarkerArray();

  for (int i = 0; i < 2; i++) {
    // 创建第一条车道线的Marker
    visualization_msgs::msg::Marker marker;
    marker.header.frame_id = "map";
    marker.header.stamp = node->now();
    marker.ns = "markers";
    marker.id = i;
    marker.action = visualization_msgs::msg::Marker::ADD;

    if (0 == i) {
      // LINE_STRIP: 一条连接所有点的线段
      // LINE_LIST: 每两个连续的点将会形成一条独立的线段
      marker.type = visualization_msgs::msg::Marker::LINE_STRIP;

      marker.pose.orientation.w = 1.0;

      marker.scale.x = 0.01;  // 线段宽度
      marker.color.r = 1.0;   // RGB
      marker.color.a = 1.0;   // 透明度
                              //
      geometry_msgs::msg::Point point;
      point.set__x(1);
      point.set__y(1);
      marker.points.emplace_back(point);
      point.set__x(2);
      point.set__y(2);
      marker.points.emplace_back(point);
      point.set__x(3);
      point.set__y(3);
      marker.points.emplace_back(point);
      point.set__x(4);
      point.set__y(4);
      marker.points.emplace_back(point);

    } else if (1 == i) {
      marker.type = visualization_msgs::msg::Marker::LINE_STRIP;

      marker.pose.orientation.w = 1.0;

      marker.scale.x = 0.1;  // 线段宽度
      marker.color.r = 1.0;  // RGB
      marker.color.a = 1.0;  // 透明度

      geometry_msgs::msg::Point point;
      point.set__x(0);
      point.set__y(0);
      marker.points.emplace_back(point);
      point.set__x(1);
      point.set__y(2);
      marker.points.emplace_back(point);
      point.set__x(2);
      point.set__y(3);
      marker.points.emplace_back(point);
      point.set__x(3);
      point.set__y(4);
      marker.points.emplace_back(point);
    }

    marker_array.markers.emplace_back(marker);
  }

  rclcpp::WallRate rate(5);
  while (rclcpp::ok()) {
    rclcpp::spin_some(node);
    pub->publish(marker_array);
    rate.sleep();
  }

  rclcpp::shutdown();
  return 0;
}
