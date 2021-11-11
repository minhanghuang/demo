/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/11/11 09:58
*/
#include "simple.h"


MyCalss::MyCalss() {
    std::cout << "MyCalss" << std::endl;
}
MyCalss::~MyCalss() {
    std::cout << "~MyCalss" << std::endl;
}

void MyCalss::func1() {
    std::cout << "func1" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // 休眠
    std::cout << "func1 --" << std::endl;
}

void MyCalss::func2() {
    std::cout << "func2" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(6000)); // 休眠
    std::cout << "func2 --" << std::endl;
}

void MyCalss::func3(int x) {
    std::cout << "func3-" << x << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(4000)); // 休眠
    std::cout << "func3 --" << std::endl;
}

void MyCalss::func4(std::string& s) {
    std::cout << "func4-" << s << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(4000)); // 休眠
    std::cout << "func4 --" << std::endl;
}

void MyCalss::func5(std::shared_ptr<Cache>& c) {
    std::cout << "func5-" << c->x << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(4000)); // 休眠
    std::cout << "func5 --" << std::endl;
}

void MyCalss::class_thread() {
    std::cout << "thread start ..." << std::endl;
    std::thread t1(&MyCalss::func1, this);
    std::thread t2(&MyCalss::func2, this);
    std::thread t3(&MyCalss::func3, this, 55);
    std::string s = "i am string";
    std::thread t4(&MyCalss::func4, this, std::ref(s));
    auto c = std::make_shared<Cache>();
    std::thread t5(&MyCalss::func5, this, std::ref(c));
    std::cout << "thread join()" << std::endl;
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    std::cout << "thread end ..." << std::endl;
}
