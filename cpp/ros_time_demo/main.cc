#include <ros/init.h>
#include <ros/rate.h>
#include <ros/ros.h>
#include <ros/spinner.h>
#include <std_msgs/String.h>

void Chatcb(const std_msgs::String& msg) {
  std::cout << msg.data.c_str() << std::endl;
}

int main(int argc, char** argv) {
  std::cout << "Hello, Ros Time!" << std::endl;
  ros::init(argc, argv, "time_demo");
  ros::NodeHandle nh;

  // {
  //   std::cout << "@@@@@ Rate: 频率 @@@@@" << std::endl;
  //   const double t = 10;  // 10Hz
  //   ros::Rate rate(t);
  //   while (ros::ok()) {
  //     ros::spinOnce();
  //     rate.sleep();
  //   }
  //   return 0;
  // }

  // {
  //   std::cout << "@@@@@ Duration: 一段时间 @@@@@" << std::endl;
  //   const double t = 0.1;  // 10Hz
  //   ros::Duration duration(t);
  //   while (ros::ok()) {
  //     ros::spinOnce();
  //     duration.sleep();
  //   }
  //   return 0;
  // }

  {
    std::cout << "@@@@@ Rate -> Duration  @@@@@" << std::endl;
    ros::Rate rate(10);
    ros::Duration duration(rate.expectedCycleTime());
    std::cout << "duration: " << duration << std::endl;  // 0.100000000 s
  }

  {
    std::cout << "@@@@@ Rate <- Duration  @@@@@" << std::endl;
    ros::Duration duration(0.1);
    ros::Rate rate(1.0 / duration.toSec());  // 10Hz
  }

  return 0;
}
