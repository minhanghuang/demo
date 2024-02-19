#include <ros/init.h>
#include <ros/ros.h>
#include <ros/spinner.h>
#include <std_msgs/String.h>

void Chatcb(const std_msgs::String& msg) {
  std::cout << msg.data.c_str() << std::endl;
}

int main(int argc, char** argv) {
  std::cout << "Hello, Ros Sub!" << std::endl;
  ros::init(argc, argv, "sub");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/chat", 10, Chatcb);

  /// 单线程
  // ros::spin();
  // while (ros::ok()) {
  //   ros::spinOnce();
  // }

  /// 多线程
  // ros::MultiThreadedSpinner spiner; // 默认机器线程数
  ros::MultiThreadedSpinner spiner(3);  // 3个线程
  spiner.spin();

  return 0;
}
