#include <iostream>
#include <tf/tf.h>
#include <nav_msgs/Odometry.h>

int main() {
    std::cout << "Hello, 四元素转欧拉角!" << std::endl;
    nav_msgs::Odometry position;
    tf::Quaternion quaternion;
    double roll,pitch,yaw;

    position.pose.pose.orientation.x = 0.00139625178541;
    position.pose.pose.orientation.y = -0.0025784220826;
    position.pose.pose.orientation.z = -0.423166269627;
    position.pose.pose.orientation.w = 0.906047300349;

    tf::quaternionMsgToTF(position.pose.pose.orientation,quaternion);
    tf::Matrix3x3(quaternion).getRPY(roll, pitch, yaw);
    std::cout<<"输出的欧拉角为：roll="<<roll<<",pitch="<<pitch<<",yaw="<<yaw<<std::endl;

    return 0;
}
