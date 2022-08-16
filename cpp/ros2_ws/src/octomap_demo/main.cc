#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>
#include <octomap_msgs/conversions.h>
#include <octomap_msgs/msg/octomap.hpp>
#include <rclcpp/rclcpp.hpp>
#include <vector>

typedef struct Point PointType;
typedef std::vector<PointType> Points;
struct Point {
  size_t x;
  size_t y;
  size_t z;
};

void ParamPoints(const std::shared_ptr<rclcpp::Node> node, Points &pts) {
  node->declare_parameter("points");
  auto param_pts = node->get_parameter("points");
  Point point;
  size_t i = 0;
  for (const auto &it : param_pts.as_integer_array()) {
    if (0 == i) {
      point.x = it;
      i++;
    } else if (1 == i) {
      point.y = it;
      i++;
    } else if (2 == i) {
      point.z = it;
      pts.emplace_back(point);
      i = 0;
    }
  }
}

void PointsToOctoMap(const Points &pts, octomap::ColorOcTree *octomap) {
  octomap->clear();
  unsigned int R = 216;
  unsigned int G = 120;
  unsigned int B = 255;
  
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      for (int k = 0; k < 20; k++) {
        octomap->updateNode(octomap::point3d(i, j, k), true);
      } 
    } 
  }

  // for (const auto &point : pts) {
    // octomap->updateNode(octomap::point3d(point.x, point.y, point.z), true);
  // }
}

void OctoMapToMsg(octomap::ColorOcTree *octomap,
                  octomap_msgs::msg::Octomap &msg) {
  msg.header.frame_id = "map";
  msg.binary = false;
  octomap_msgs::fullMapToMsg(*octomap, msg);
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("octomap_demo_node");
  auto pub =
      node->create_publisher<octomap_msgs::msg::Octomap>("/pub_octomap", 1);
  rclcpp::WallRate r(1);

  Points pts;
  ParamPoints(node, pts);
  octomap::ColorOcTree *octomap = new octomap::ColorOcTree(0.5);
  octomap_msgs::msg::Octomap msg;
  PointsToOctoMap(pts, octomap);
  OctoMapToMsg(octomap, msg);

  while (rclcpp::ok()) {
    pub->publish(msg);
    rclcpp::spin_some(node);
    r.sleep();
  }

  rclcpp::shutdown();
  return 0;
}
