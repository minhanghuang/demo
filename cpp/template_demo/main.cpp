#include <iostream>
#include "src/core.h"

// https://www.liangzl.com/get-article-detail-168919.html
// https://ask.csdn.net/questions/816134

int main() {
    std::cout << "Hello, Template!" << std::endl;
    Lane lane;
    lane.get();
    std::cout << "---\n" << std::endl;
    Point p1{};
    p1.x = 1.2;
    Section section;
    section.get<Point>(p1);
    std::cout << "---\n" << std::endl;
    Point p2{};
    p2.x = 1.2;
    Road<Point> road;
    auto t = road.get<Point>(p2);
    std::cout << "t:" << t.x << std::endl;
    return 0;
}


