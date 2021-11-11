/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/11/11 09:58
*/
#ifndef THREAD_DEMO_SIMPLE_H
#define THREAD_DEMO_SIMPLE_H
#include <iostream>
#include <thread>
#include <memory>

void func1(){
    std::cout << "func1" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // 休眠
    std::cout << "func1 --" << std::endl;
}
void func2(){
    std::cout << "func2" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(6000)); // 休眠
    std::cout << "func2 --" << std::endl;
}

void func_thread() {
    std::cout << "thread start ..." << std::endl;
    std::thread t1(func1);
    std::thread t2(func2);
    std::cout << "thread join()" << std::endl;
    t1.join();
    t2.join();
    std::cout << "thread end ..." << std::endl;
}

struct Cache {
    double x = 98776.2;
};

class MyCalss{
public:
    MyCalss();
    ~MyCalss();
    void func1();
    void func2();
    void func3(int x);
    void func4(std::string& s);
    void func5(std::shared_ptr<Cache>& c);
    void class_thread();
};

#endif//THREAD_DEMO_SIMPLE_H
