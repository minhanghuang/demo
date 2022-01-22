#include <iostream>
#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <rosbag/query.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/impl/pcl_base.hpp>
#include <velodyne_msgs/VelodynePacket.h>
#include <velodyne_msgs/VelodyneScan.h>


/// 全量信息的点云（带height(高度),range(度量),ring(第几圈))
struct PointXYZIHIRBS {
    PCL_ADD_POINT4D;
    float height;
    float range;
    uint8_t intensity;
    uint8_t intensity_vi;
    uint8_t ring;
    uint8_t type;
    inline PointXYZIHIRBS() {
        x = y = z = 0.0f;
        intensity = intensity_vi = ring = type = 0;
        height = range = 0.0f;
    }
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};


POINT_CLOUD_REGISTER_POINT_STRUCT(PointXYZIHIRBS,
(float, x, x)(float, y, y)(float, z, z)(std::uint8_t, intensity, intensity)(
float, height, height)(std::uint8_t, intensity_vi, intensity_vi)(
float, range, range)(std::uint8_t, ring, ring)(std::uint8_t, type, type))


int main(int argc, char **argv) {
    std::cout << "Hello, Velodyne!" << std::endl;

    ros::init(argc, argv, "velodyne_demo");
    ros::NodeHandle nh;
    rosbag::Bag bag;
    bag.open("/home/mapdev/data/hdmap/A001/A1.bag", rosbag::bagmode::Read);

    for (const auto& m : rosbag::View(bag)) {
        if ("/vlp16_1/velodyne_packets" == m.getTopic()) {
            auto v16 = m.instantiate<velodyne_msgs::VelodyneScan>();
            if (v16 != nullptr) {
              for (const auto& packet : v16->packets) {
                const auto* data = packet.data.data();

              }
            }
        }
    }

    return 0;
}
