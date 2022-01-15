#include <iostream>
#include <unistd.h>
#include <trunk/cater/znode.h>
#include <trunk/msgs/hdmap.pb.h>

using namespace trunk;

int main() {
    std::cout << "Hello, Znode Pub!" << std::endl;
    cater::ZNode znode;
    std::string channel = "ipc:///var/log/trunk/haha.ipc";
    msgs::Position position;
    position.mutable_point()->set_x(1);
    position.mutable_point()->set_y(2);
    position.mutable_point()->set_z(3);
    while (true) {
        sleep(1);
        znode.channel(channel,1, cater::ZNode::PUB).pub("/haha/hdmap", position);
        std::cout << position.DebugString() << std::endl;
    }
    return 0;
}
