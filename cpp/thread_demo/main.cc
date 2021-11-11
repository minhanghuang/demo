#include <iostream>
#include "src/simple.h"
#include "src/pool.h"

int main() {
    std::cout << "Hello, Thread!" << std::endl;
//    func_thread();
//    MyCalss instance;
//    instance.class_thread();
    pool::MyCalss instance2;
    instance2.class_thread();
    return 0;
}
