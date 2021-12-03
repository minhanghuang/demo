/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Minhang Huang <huangminhang@trunk.tech>, 2021/12/2 22:48
*/
#ifndef TEMPLATE_DEMO_CORE_H
#define TEMPLATE_DEMO_CORE_H
#include <iostream>

struct Point {
    double x;
    double y;
    double z;
};


class Lane {
public:
    ~Lane();
    Lane();
    void get();
};

class Section {
public:
    ~Section();
    Section();
    template<typename T>
    void get(T p) {
        std::cout << "Section get:" << p.x << std::endl;
    }
};

template<typename T>
class Road {
public:
    ~Road() {

    }
    Road() {

    }
    template<typename P>
    T get(P p) {
        std::cout << "Road get:" << p.x << std::endl;
        T t;
        t.x = 999;
        return t;
    }
};

#endif//TEMPLATE_DEMO_CORE_H
