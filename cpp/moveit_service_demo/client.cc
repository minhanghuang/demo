#include "moveit_msgs/JointConstraint.h"
#include "ros/duration.h"
#include <cstdlib>
#include <iostream>
#include <moveit_msgs/GetMotionPlan.h>
#include <ros/ros.h>
#include <vector>


int main(int argc, char *argv[]) {
  ros::init(argc, argv, "moveit_client");
  ros::NodeHandle n;
  ros::ServiceClient client =
      n.serviceClient<moveit_msgs::GetMotionPlan>("moveit_test");
  moveit_msgs::GetMotionPlan srv;
  srv.request.motion_plan_request.group_name = "name";

  moveit_msgs::PositionConstraint pc;
  moveit_msgs::OrientationConstraint oc;
  
  oc.orientation.x = 1.0;
  oc.orientation.y = 1.1;
  oc.orientation.z = 1.2;
  oc.orientation.w = 1.3;
  
  moveit_msgs::Constraints pose_goal;
  pose_goal.position_constraints.push_back(pc);
  pose_goal.orientation_constraints.push_back(oc);

  srv.request.motion_plan_request.goal_constraints.push_back(pose_goal);

  client.waitForExistence(ros::Duration(3));
  if (client.call(srv)) {
    std::cout << "call " << std::endl;
  }
  return 0;
}
