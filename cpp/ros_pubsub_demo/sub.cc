/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/11/23 15:01
*/
#include <iostream>
#include <ros/ros.h>
#include <std_msgs/String.h>


void chatterCallback(const std_msgs::String::ConstPtr& msg) {
    std::cout << msg->data.c_str() << std::endl;
}

int main(int argc, char **argv) {
    std::cout << "Hello, ROS Sub!" << std::endl;

    ros::init(argc, argv, "listener");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
    ros::spin();

    return 0;
}


