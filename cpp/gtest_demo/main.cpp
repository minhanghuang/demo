#include <iostream>
#include <gtest/gtest.h>
#include "src/env.cc"


int add(int a,int b){
    return a+b;
}

TEST(testCase,test0){
    std::cout << "getEn:   " << TestEnvironment::getEn() << std::endl;
    EXPECT_EQ(add(2,3),5);
}

int main(int argc,char *argv[]) {
    testing::AddGlobalTestEnvironment(new TestEnvironment);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
