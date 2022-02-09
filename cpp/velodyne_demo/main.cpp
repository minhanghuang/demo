#include <iostream>
#include "src/transform.h"


int main(int argc, char **argv) {
    std::cout << "Hello, Velodyne!" << std::endl;

    ros::init(argc, argv, "velodyne_demo");
    ros::NodeHandle nh;
    rosbag::Bag bag;
    bag.open("/home/mapdev/data/hdmap/A001/A1.bag", rosbag::bagmode::Read);
    VLP16Parser parser("conf/VLP-16.yaml");
    pcl::PointCloud<PointXYZIHIRBS> cloud;

    for (const auto& m : rosbag::View(bag)) {
        if ("/vlp16_1/velodyne_packets" == m.getTopic()) {
            auto v16 = m.instantiate<velodyne_msgs::VelodyneScan>();
            if (v16 != nullptr) {
              for (const auto& packet : v16->packets) {
                const auto* data = packet.data.data();
                RawPacket pkt{};
                pkt.set(data);
                if (parser.PacketToPoint(pkt, cloud)) {
                  std::cout << "size:" << cloud.points.size() << std::endl;
                  cloud.clear();
                }
              }
            }
        }
    }

    return 0;
}
