/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/11/23 15:02
*/
#include <iostream>
#include <ros/ros.h>
#include <std_msgs/String.h>


int main(int argc, char **argv) {
    std::cout << "Hello, ROS Pub!" << std::endl;
    ros::init(argc, argv, "talker");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<std_msgs::String>("chatter", 1);
    ros::Rate loop_rate(10);
    int count = 0;
    while (ros::ok()) {
        std_msgs::String msg;
        std::stringstream ss;
        ss << "hello world " << count;
        msg.data = ss.str();
        pub.publish(msg);
        loop_rate.sleep();
        ++count;
    }
    return 0;
}

