#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/detail/point_cloud2__struct.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <std_msgs/msg/string.hpp>


int main(int argc, char **argv) {
  std::cout << "Hello, ROS2 PCL!" << std::endl;

  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("pcl2octo_node");
  auto pub = node->create_publisher<sensor_msgs::msg::PointCloud2>("/pcl2octo", 1);
  size_t num_points = 100;
  pcl::PointCloud<pcl::PointXYZRGB> cloud;
  cloud.points.resize(num_points);
  sensor_msgs::msg::PointCloud2 output_msg;

  for (int i = 0; i < num_points; i++) {
    cloud.points[i].x = 10 * rand() / (RAND_MAX + 1.0f);
    cloud.points[i].y = 10 * rand() / (RAND_MAX + 1.0f);
    cloud.points[i].z = 10 * rand() / (RAND_MAX + 1.0f);
    cloud.points[i].r = (rand() % (255 + 1)); //(rand() % (b-a+1))+ a
    cloud.points[i].g = (rand() % (255 + 1));
    cloud.points[i].b = (rand() % (255 + 1));
  }

  pcl::toROSMsg(cloud, output_msg); 
  output_msg.header.frame_id = "map";

  rclcpp::WallRate r(5);
  while (rclcpp::ok()) {
    RCLCPP_INFO(node->get_logger(), "pub");
    pub->publish(output_msg);
    rclcpp::spin_some(node);
    r.sleep();
  }

  rclcpp::shutdown();
  return 0;
}
