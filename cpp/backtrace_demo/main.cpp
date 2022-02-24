#include <iostream>
#include "src/stacktrace.h"


int main(int argc, char **argv) {
    std::cout << "stack trace" << std::endl;
    stack::InstallFailureSignalHandler();
    std::vector<int> a{1,2,3};
    std::cout << a.at(100) << std::endl;
    return 0;
}
