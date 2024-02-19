#include <ros/ros.h>
#include <roscpp_tutorials/TwoInts.h>
#include <iostream>

class AddTwo {
 public:
  bool add(roscpp_tutorials::TwoInts::Request& req,
           roscpp_tutorials::TwoInts::Response& res) {
    res.sum = req.a + req.b;
    std::cout << "req: " << req.a << "," << req.b << std::endl;
    return true;
  }
};


int main(int argc, char* argv[]) {
  std::cout << "ros server" << std::endl;
  ros::init(argc, argv, "add_two_ints_server");
  ros::NodeHandle n;
  AddTwo a;
  ros::ServiceServer ss = n.advertiseService("add_two_ints", &AddTwo::add, &a);
  ros::spin();
  return 0;
}
