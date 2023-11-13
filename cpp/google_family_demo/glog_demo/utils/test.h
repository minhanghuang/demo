#ifndef GLOG_DEMO_TEST_H_
#define GLOG_DEMO_TEST_H_
#include <iostream>
#include <vector>

class MyTest {
public:
  MyTest()=default;
  void Run() {
    std::vector<int> a{1,2};
    std::cout << a.at(100) << std::endl;
  }
};

#endif // GLOG_DEMO_TEST_H_
