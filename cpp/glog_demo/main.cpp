#include <iostream>
#include <vector>
#include <csignal>
#include "utils/log.h"
#include "utils/test.h"


int main(int argc, char **argv) {
    std::vector<int> v;
    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(992);
//    Log::init(google::GLOG_FATAL);
    Log::init(google::GLOG_INFO);
    LOG(ERROR) << "There is error !!!";
    LOG(INFO) << "There is info !!! " << v;
//    raise(SIGINT);
    MyTest t;
    t.Run();
    MLOG_INFO("-------------");
    return 0;
}
