#include <iostream>
#include <unistd.h>
#include <trunk/cater/znode.h>
#include <trunk/msgs/hdmap.pb.h>

using namespace trunk;

void hdmap_callback(const msgs::Position& msg) {
    std::cout << "hdmap_callback:" << msg.DebugString() << std::endl;
    std::cout << "---" << std::endl;
}

int main() {
    std::cout << "Hello, Znode Sub!" << std::endl;
    cater::ZNode znode;
    std::string channel = "ipc:///var/log/trunk/haha.ipc";

    znode.channel(channel, 1, cater::ZNode::SUB)
        .sub<msgs::Position>("/haha/hdmap", hdmap_callback)
        .start();

    while (true) {
        znode.spin_once();
    }
    return 0;
}
