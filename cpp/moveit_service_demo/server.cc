#include <iostream>
#include <moveit_msgs/GetMotionPlan.h>
#include <ros/ros.h>

bool test(moveit_msgs::GetMotionPlan::Request &req,
          moveit_msgs::GetMotionPlan::Response &res) {
  std::cout << "req: ---" << std::endl;
  auto oc = req.motion_plan_request.goal_constraints.front().orientation_constraints.front();

  std::cout << "x:" << oc.orientation.x << std::endl;
  std::cout << "y:" << oc.orientation.y << std::endl;
  std::cout << "z:" << oc.orientation.z << std::endl;
  std::cout << "w:" << oc.orientation.w << std::endl;

  return true;
}

int main(int argc, char *argv[]) {
  std::cout << "ros server" << std::endl;
  ros::init(argc, argv, "movit_server");
  ros::NodeHandle n;
  ros::ServiceServer ss = n.advertiseService("moveit_test", test);
  ros::spin();
  return 0;
}
