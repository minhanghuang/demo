#include <iostream>
#include <ros/ros.h>
#include <roscpp_tutorials/TwoInts.h>
#include <cstdlib>



int main(int argc, char *argv[]) {
  std::cout << "ros client" << std::endl;
  ros::init(argc, argv, "add_two_ints_client");
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<roscpp_tutorials::TwoInts>("add_two_ints");
  roscpp_tutorials::TwoInts srv;
  srv.request.a = 1;
  srv.request.b = 3;
  if (client.call(srv)) {
    std::cout << "call " << srv.response.sum << std::endl;
  }
  return 0;
}
