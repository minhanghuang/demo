/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Minhang Huang <huangminhang@trunk.tech>, 2021/12/7 09:46
*/
#include <iostream>
#include <map>
#include <gtest/gtest.h>
#include "env.cc"


class TestMap : public testing::Test {
public:
    //添加日志
    static void SetUpTestCase() {
        std::cout << "SetUpTestCase" << std::endl;
    }
    static void TearDownTestCase() {
        std::cout << "TearDownTestCase" << std::endl;
    }
    virtual void SetUp() { // 每个TEST跑之前会执行SetUp
        std::cout << "SetUp" << std::endl;
        test_map.insert(std::make_pair(1, 0));
        test_map.insert(std::make_pair(2, 1));
        test_map.insert(std::make_pair(3, 2));
        test_map.insert(std::make_pair(4, 3));
        test_map.insert(std::make_pair(5, 4));
    }
    virtual void TearDown() { // 每个TEST跑完之后会执行TearDown
        std::cout << "TearDown" << std::endl;
        test_map.clear();
    }
    std::map<int, int> test_map;
};

TEST_F(TestMap, Find) {
    std::map<int, int>::iterator it = test_map.find(1);
    std::cout << "getEn:   " << TestEnvironment::getEn() << std::endl;
    ASSERT_NE(it, test_map.end());
}

TEST_F(TestMap, Size) {
    std::cout << "getEn:   " << TestEnvironment::getEn() << std::endl;
    ASSERT_EQ(test_map.size(), 5);
}
