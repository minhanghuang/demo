#include <iostream>
#include <memory>
#include <ros/ros.h>
#include <velodyne_msgs/VelodyneScan.h>
#include<sensor_msgs/PointCloud2.h>
#include<pcl_conversions/pcl_conversions.h>
#include "src/transform.h"


class Subscriber {
public:
    Subscriber(){
        vlp32_1_parser_ = std::make_shared<VLP32Parser>("conf/VLP-32C.yaml");
        vlp32_2_parser_ = std::make_shared<VLP32Parser>("conf/VLP-32C.yaml");
    }
    void Init(){
        pub_1_ = n_.advertise<sensor_msgs::PointCloud2> ("pcl_1", 1);
        pub_2_ = n_.advertise<sensor_msgs::PointCloud2> ("pcl_2", 1);
        sub1_ = n_.subscribe("/vlp32_0/velodyne_packets", 1, &Subscriber::v321Callback, this);
        sub2_ = n_.subscribe("/vlp32_2/velodyne_packets", 1, &Subscriber::v322Callback, this);
    }
    void Run(){
        ros::Rate r(10);
        while (ros::ok()) {
            ros::spinOnce();
            r.sleep();
        }
    }

private:
    void v321Callback(const velodyne_msgs::VelodyneScan& msg) {
        for (const auto& packet : msg.packets) {
            const auto* data = packet.data.data();
            RawPacket pkt{};
            pkt.set(data);
            if (vlp32_1_parser_->PacketToPoint(pkt, cloud1_)) {
                pcl::toROSMsg(cloud1_, output_1_);
                output_1_.header.frame_id = "lidar_left";
                pub_1_.publish(output_1_);
                cloud1_.clear();
            }
        }
    }
    void v322Callback(const velodyne_msgs::VelodyneScan& msg) {
        for (const auto& packet : msg.packets) {
            const auto* data = packet.data.data();
            RawPacket pkt{};
            pkt.set(data);
            if (vlp32_2_parser_->PacketToPoint(pkt, cloud2_)) {
                output_2_.data.clear();
                pcl::toROSMsg(cloud2_, output_2_);
                output_2_.header.frame_id = "lidar_right";
                pub_2_.publish(output_2_);
                cloud2_.clear();
            }
        }
    }
    ros::NodeHandle n_;
    ros::Publisher pub_1_,pub_2_;
    ros::Subscriber sub1_;
    ros::Subscriber sub2_;
    sensor_msgs::PointCloud2 output_1_,output_2_;
    std::shared_ptr<VLP32Parser> vlp32_1_parser_;
    std::shared_ptr<VLP32Parser> vlp32_2_parser_;
    pcl::PointCloud<PointXYZIHIRBS> cloud1_,cloud2_;
};


int main(int argc, char **argv) {
    std::cout << "Hello, PCL!" << std::endl;
    ros::init(argc, argv, "packet2pcl");
    Subscriber sub;
    sub.Init();
    sub.Run();
    return 0;
}
