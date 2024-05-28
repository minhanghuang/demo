#include <cstdlib>
#include <functional>
#include <string>
#include <vector>

#include <ros/init.h>
#include <ros/rate.h>
#include <ros/ros.h>
#include <ros/spinner.h>
#include <ros/time.h>
#include <std_msgs/String.h>

#include "ros/duration.h"

void TimerCallback(const ros::TimerEvent& event, const std::string& id) {
  std::cout << id << "  TimerCallback" << std::endl;
}

int main(int argc, char** argv) {
  std::cout << "Hello, Ros Timer!" << std::endl;
  ros::init(argc, argv, "timer_demo");
  ros::NodeHandle nh;
  std::vector<ros::Timer> timers;

  {
    std::cout << "timer callback 传参数" << std::endl;
    for (int i = 0; i < 3; i++) {
      timers.emplace_back(nh.createTimer(
          ros::Duration(0.1),
          std::bind(&TimerCallback, std::placeholders::_1, std::to_string(i))));
    }
  }

  ros::spin();

  return EXIT_SUCCESS;
}
