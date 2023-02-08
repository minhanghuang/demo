#include <ros/ros.h>
#include <std_msgs/String.h>

int main(int argc, char** argv) {
  std::cout << "Hello, Ros Pub!" << std::endl;
  ros::init(argc, argv, "pub");
  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<std_msgs::String>("/chat", 1);
  ros::Rate r(5);
  std_msgs::String msg;
  msg.data = "hello";
  while (ros::ok()) {
    pub.publish(msg);
    r.sleep();
  }
  return 0;
}
