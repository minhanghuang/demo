#include <iostream>
#include <iomanip>
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
        tf2::Transform tmp_tf;
        tf2::fromMsg(m_tf_utm_point.transform, tmp_tf);
        geometry_msgs::TransformStamped tf_convert;
        tf_convert.transform = tf2::toMsg(tmp_tf.inverse());
        tf_convert.child_frame_id = m_tf_utm_point.header.frame_id;
        tf_convert.header.frame_id = m_tf_utm_point.child_frame_id;
        int count = 0;
        for (const auto& point : msg.sections.front().lanes.front().pts_center) {
            std::cout << std::setprecision(10) << "[" << point.point.x << "," << point.point.y << "," << point.point.z << "]" << std::endl;
            geometry_msgs::Point tf_point;
            tf2::doTransform(point.point,tf_point,tf_convert);
            std::cout << std::setprecision(10) << "[" << tf_point.x << "," << tf_point.y << "," << tf_point.z << "]" << std::endl;
            if (count>5) {
                break;
            }
            count++;
        }
        std::cout << "----" << std::endl;
    }
    void callback_tf(const tf2_msgs::TFMessage& msg) {
        std::cout << "callback_tf" << std::endl;
        m_tf_utm_point.transform.translation.x = msg.transforms.front().transform.translation.x;
        m_tf_utm_point.transform.translation.y = msg.transforms.front().transform.translation.y;
        m_tf_utm_point.transform.translation.z = msg.transforms.front().transform.translation.z;

        m_tf_utm_point.transform.rotation.x = msg.transforms.front().transform.rotation.x;
        m_tf_utm_point.transform.rotation.y = msg.transforms.front().transform.rotation.y;
        m_tf_utm_point.transform.rotation.z = msg.transforms.front().transform.rotation.z;
        m_tf_utm_point.transform.rotation.w = msg.transforms.front().transform.rotation.w;

        m_tf_utm_point.header.frame_id = "utm";
        m_tf_utm_point.child_frame_id = "smartcar";
    }
    ros::Subscriber m_sub_localmap;
    ros::Subscriber m_sub_tf;
    geometry_msgs::TransformStamped m_tf_utm_point;
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
