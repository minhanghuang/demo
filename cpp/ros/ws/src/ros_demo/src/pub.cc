#include <iostream>

#include <ros/ros.h>
#include <std_msgs/String.h>

int main(int argc, char** argv) {
  std::cout << "Hello, Ros Pub!" << std::endl;
  ros::init(argc, argv, "ros_demo_pub_node");
  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<std_msgs::String>("/demo/pub1", 1);
  ros::Rate r(5);
  std_msgs::String msg;
  msg.data = "hello";

  while (ros::ok()) {
    pub.publish(msg);
    r.sleep();
  }

  return 0;
}
