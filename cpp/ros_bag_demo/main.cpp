#include <iostream>
#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <rosbag/query.h>
#include <boost/foreach.hpp>


int main(int argc, char** argv) {
    std::cout << "Hello, Ros Bag!" << std::endl;

    ros::init (argc, argv, "ros_bag_demo");
    ros::NodeHandle nh;
    rosbag::Bag bag;
    bag.open("/home/trunk/work/data/bags/test.bag", rosbag::bagmode::Read);
    rosbag::View view(bag);

    // 获取bag包的info
    std::vector<const rosbag::ConnectionInfo *> connection_infos = view.getConnections();

    BOOST_FOREACH(const rosbag::ConnectionInfo *info, connection_infos) {
        std::cout << "info: " << info->topic << std::endl;
        std::cout << "datatype: " << info->datatype << std::endl;
        std::cout << "id: " << info->id << std::endl;
        std::cout << "md5sum: " << info->md5sum << std::endl;
        std::cout << "---" << std::endl;
    }

    // 获取bag包的数据帧
    rosbag::View::iterator it = view.begin();
    for(; it !=  view.end(); ++it) {
        auto m = *it;
        const std::string& topic   = m.getTopic();
        const std::string& type   = m.getDataType();
        auto t  = m.getTime();
//        std::cout << "type:" << type << std::endl;
//        std::cout << "toSec:" << t.toSec() << std::endl;
//        std::cout << "toNSec:" << t.toNSec() << std::endl;
//        std::cout << "topic:" << topic << std::endl;
//        std::cout << "----" << std::endl;
    }

    bag.close();

    return 0;
}
