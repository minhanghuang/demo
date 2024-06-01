#include <rviz_common/logging.hpp>
#include <rviz_plugin_tutorial/point_display.hpp>

namespace rviz_plugin_tutorial {
void PointDisplay::processMessage(
    const geometry_msgs::msg::Point2D::ConstSharedPtr msg) {
  RVIZ_COMMON_LOG_INFO_STREAM("We got a message with frame "
                              << msg->header.frame_id);
}
}  // namespace rviz_plugin_tutorial

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(rviz_plugin_tutorial::PointDisplay, rviz_common::Display)
