#include <iostream>
#include "src/server.h"

int main() {
    std::cout << "Hello, Civetweb 封装!" << std::endl;
    HttpServer server(9090);
    server.init();
    server.run();
    return 0;
}
