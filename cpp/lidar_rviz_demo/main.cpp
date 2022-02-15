#include <iostream>
#include<ros/ros.h>
#include<pcl/point_cloud.h>
#include<pcl/io/pcd_io.h>
#include<pcl_conversions/pcl_conversions.h>
#include<sensor_msgs/PointCloud2.h>


int main(int argc, char **argv) {
    std::cout << "Hello, PCL11!" << std::endl;
    ros::init (argc, argv, "pcl_demo");
    ros::NodeHandle nh;
    ros::Publisher pcl_pub = nh.advertise<sensor_msgs::PointCloud2> ("pcl", 1);
    pcl::PointCloud<pcl::PointXYZ> cloud;
    sensor_msgs::PointCloud2 output;
    cloud.width = 100;
    cloud.height = 1;
    cloud.points.resize(cloud.width * cloud.height);
    for (auto & point : cloud.points) {
        point.x = 1024 * rand () / (RAND_MAX + 1.0f);
        point.y = 1024 * rand () / (RAND_MAX + 1.0f);
        point.z = 1024 * rand () / (RAND_MAX + 1.0f);
    }
    //Convert the cloud to ROS message
    pcl::toROSMsg(cloud, output);
    output.header.frame_id = "smartcar";//this has been done in order to be able to visualize our PointCloud2 message on the RViz visualizer
    ros::Rate loop_rate(1);
    pcl::io::savePCDFileASCII("/home/trunk/work/code/test/demo/lidar_rviz_demo/build/test_pcd.pcd", cloud);
    while (ros::ok()) {
        pcl_pub.publish(output);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
