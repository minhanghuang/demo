#include <iostream>
#include <memory>
#include <ros/ros.h>
#include <velodyne_msgs/VelodyneScan.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/common/transformation_from_correspondences.h> // pcl::getTransformation
#include <pcl/common/transforms.h>	//	pcl::transformPointCloud
#include <Eigen/Eigen>
#include "src/transform.h"


class Subscriber {
public:
    Subscriber(){
        vlp32_1_parser_ = std::make_shared<VLP32Parser>("conf/VLP-32C.yaml");
        vlp32_2_parser_ = std::make_shared<VLP32Parser>("conf/VLP-32C.yaml");
        // left
        trans1_ = pcl::getTransformation(5.4, 1.2, 1.52, 0.01, -0.01, 1.0);
        // right
        trans2_ = pcl::getTransformation(5.4, -1.2, 1.52, 0.01, -0.01, -0.87);
    }
    void Init(){
        pub_1_ = n_.advertise<sensor_msgs::PointCloud2> ("pcl_1", 1);
        pub_2_ = n_.advertise<sensor_msgs::PointCloud2> ("pcl_2", 1);
        pub_3_ = n_.advertise<sensor_msgs::PointCloud2> ("pcl_3", 1);
        sub1_ = n_.subscribe("/vlp32_0/velodyne_packets", 1, &Subscriber::v321Callback, this);
        sub2_ = n_.subscribe("/vlp32_2/velodyne_packets", 1, &Subscriber::v322Callback, this);
    }
    void Run(){
        ros::Rate r(10);
        while (ros::ok()) {
            ros::spinOnce();
            PubAllPointCloud();
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
//                // 左雷达 frame_id
//                pcl::toROSMsg(cloud1_, output_1_);
//                output_1_.header.frame_id = "lidar_left";
//                pub_1_.publish(output_1_);
//                cloud1_.clear();

                // 车体 frame_id
                output_2_.data.clear();
                cloud1_car_.clear();
                pcl::transformPointCloud(cloud1_, cloud1_car_, trans1_);
                pcl::toROSMsg(cloud1_car_, output_1_);
                output_1_.header.frame_id = "smartcar";
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
//                // 右雷达 frame_id
//                output_2_.data.clear();
//                pcl::toROSMsg(cloud2_, output_2_);
//                output_2_.header.frame_id = "lidar_right";
//                pub_2_.publish(output_2_);
//                cloud2_.clear();

                // 车体 frame_id
                output_2_.data.clear();
                cloud2_car_.clear();
                pcl::transformPointCloud(cloud2_, cloud2_car_, trans2_);
                pcl::toROSMsg(cloud2_car_, output_2_);
                output_2_.header.frame_id = "smartcar";
                pub_2_.publish(output_2_);
                cloud2_.clear();
            }
        }
    }
    void PubAllPointCloud() {
        cloud_ = cloud1_car_ + cloud2_car_;
        output_3_.data.clear();
        pcl::toROSMsg(cloud_, output_3_);
        output_3_.header.frame_id = "smartcar";
        pub_3_.publish(output_3_);
    }

    ros::NodeHandle n_;
    ros::Publisher pub_1_,pub_2_,pub_3_;
    ros::Subscriber sub1_;
    ros::Subscriber sub2_;
    sensor_msgs::PointCloud2 output_1_,output_2_,output_3_;
    std::shared_ptr<VLP32Parser> vlp32_1_parser_;
    std::shared_ptr<VLP32Parser> vlp32_2_parser_;
    pcl::PointCloud<PointXYZIHIRBS> cloud1_,cloud2_,cloud1_car_,cloud2_car_, cloud_;
    Eigen::Affine3f trans1_,trans2_;
};


int main(int argc, char **argv) {
    std::cout << "Hello, PCL!" << std::endl;
    ros::init(argc, argv, "packet2pcl");
    Subscriber sub;
    sub.Init();
    sub.Run();
    return 0;
}
