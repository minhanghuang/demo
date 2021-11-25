#include <iostream>
#include <iomanip>
#include <geometry_msgs/TransformStamped.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2/LinearMath/Transform.h>
#include <geometry_msgs/Pose.h>


int main() {
    std::cout << "Hello, TF2!" << std::endl;
    geometry_msgs::TransformStamped tf_utm_point;
    geometry_msgs::Pose p1,p2;

    tf_utm_point.transform.translation.x = 567503.699966;
    tf_utm_point.transform.translation.y = 4315155.1276;
    tf_utm_point.transform.translation.z = 0;

    tf_utm_point.transform.rotation.x = 0;
    tf_utm_point.transform.rotation.y = 0;
    tf_utm_point.transform.rotation.z = -0.341415749597;
    tf_utm_point.transform.rotation.w = 0.939912382048;

    tf_utm_point.header.frame_id = "utm";
    tf_utm_point.child_frame_id = "smartcar";


    tf2::Transform tmp_tf;
    tf2::fromMsg(tf_utm_point.transform, tmp_tf);
    geometry_msgs::TransformStamped tf_convert;
    tf_convert.transform = tf2::toMsg(tmp_tf.inverse());
    tf_convert.child_frame_id = tf_utm_point.header.frame_id;
    tf_convert.header.frame_id = tf_utm_point.child_frame_id;


    p1.position.x = 567502.699966;
    p1.position.y = 4315151.1276;
    p1.position.z = 0;

    tf2::doTransform(p1,p2,tf_convert);

    std::cout << std::setprecision(10) << "[" << p2.position.x << "," << p2.position.y << "," << p2.position.z << "]" << std::endl;

    return 0;
}