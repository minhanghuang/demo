#include <cstdint>
#include <iostream>

#include <ros/init.h>
#include <ros/ros.h>
#include <ros/time.h>

int main(int argc, char** argv) {
  std::cout << "Hello, Ros Test!" << std::endl;
  ros::init(argc, argv, "test");
  ros::NodeHandle n;

  {
    std::cout << "@@@@@  时间  @@@@@" << std::endl;
    ros::Time now = ros::Time::now();
    std::cout << "sec: " << now.sec << std::endl;
    std::cout << "nsec: " << now.nsec << std::endl;
    ros::Time time_2 = ros::Time(1697619117, 370901235);  // 2023/10/18 16:52
    ros::Duration time_difference = now - time_2;
    double seconds = time_difference.toSec();  // 时间差的秒数
    int64_t milliseconds =
        time_difference.toNSec() / 1e6;  // 时间差的毫秒数(必须int64)
    int64_t nanoseconds = time_difference.toNSec();  // 时间差的纳秒数
    std::cout << "时间差(s): " << seconds << std::endl;        // 150.069
    std::cout << "时间差(ms): " << milliseconds << std::endl;  // 150069
    std::cout << "时间差(ns): " << nanoseconds << std::endl;   // 150068701961
  }
  return 0;
}
