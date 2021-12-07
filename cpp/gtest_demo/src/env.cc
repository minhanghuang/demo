/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Minhang Huang <huangminhang@trunk.tech>, 2021/12/7 10:09
*/
#include <iostream>
#include <gtest/gtest.h>


class TestEnvironment : public ::testing::Environment {
    virtual void SetUp() {
        std::cout << "TestEnvironment SetUP" << std::endl;
    }
    virtual void TearDown() {
        std::cout << "TestEnvironment TearDown" << std::endl;
    }

public:
    static std::string getEn() {
        return std::string("98765");
    }
};