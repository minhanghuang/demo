#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <cstdlib>


int main() {
    std::cout << "Hello, Cpp Shell!" << std::endl;
    // 1. 方式一
    std::string cmd;
    cmd = "ps -ef| grep python";
    system(cmd.c_str());
//    system("tar -zxvf /Users/cox/work/code/github/demo/cpp/shell_demo/haha.tar.gz");

    return 0;
}
