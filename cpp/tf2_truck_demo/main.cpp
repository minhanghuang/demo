#include <iostream>
#include <ros/ros.h>
#include <hadmap_msgs/Map.h>
#include <hadmap_msgs/Lane.h>
#include <localization_msgs/VehicleState.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Transform.h>
#include <tf2_msgs/TFMessage.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>


class Subscribe{
public:
    Subscribe(){
        m_sub_localmap = m_node.subscribe("/hadmap_server/local_map", 1, &Subscribe::callback_local_map, this);
        m_sub_tf = m_node.subscribe("/tf", 1, &Subscribe::callback_tf, this);
    }

private:
    void callback_local_map(const hadmap_msgs::Map& msg) {
        std::cout << "callback_local_map" << std::endl;
    }
    void callback_tf(const tf2_msgs::TFMessage& msg) {
        std::cout << "callback_tf" << std::endl;
    }
    ros::Subscriber m_sub_localmap;
    ros::Subscriber m_sub_tf;
    ros::NodeHandle m_node;
};

int main(int argc, char **argv) {
    std::cout << "Hello, TF!" << std::endl;
    ros::init(argc, argv, "demo_tf2");
    Subscribe sub;
    ros::Rate r(20);
    while (ros::ok()) {
        ros::spinOnce();
        r.sleep();
    }
    return 0;
}
