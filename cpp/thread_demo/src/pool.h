/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/11/11 10:42
*/
#ifndef THREAD_DEMO_POOL_H
#define THREAD_DEMO_POOL_H
#include <iostream>
#include <thread>
#include <memory>
#include <boost/thread/thread.hpp>

namespace pool {
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

    private:
        boost::thread_group m_threadpool;

    };
}

#endif//THREAD_DEMO_POOL_H
