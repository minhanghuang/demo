#include <iostream>
#include "src/log.h"

using namespace tlog;

int main() {
    std::cout << "Hello, spdlog!" << std::endl;
    XLOG->info("00000");
    return 0;
}
