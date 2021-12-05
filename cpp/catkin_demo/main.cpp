#include <iostream>
#include <ros/ros.h>
#include <std_msgs/String.h>


int main(int argc, char **argv) {
    std::cout << "Hello, Catkin!" << std::endl;
    ros::init(argc, argv, "catkin_demo_node");
    ros::NodeHandle node;
    ros::Rate r(20);
    while (ros::ok()) {
        ros::spinOnce();
        r.sleep();
    }
    return 0;
}
