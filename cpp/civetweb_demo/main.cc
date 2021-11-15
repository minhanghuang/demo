#include <iostream>
#include "src/server.h"

int main() {
    std::cout << "Hello, Civetweb!" << std::endl;
    HttpServer server;
    server.run();
    return 0;
}
