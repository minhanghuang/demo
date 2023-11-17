#include <cassert>
#include <vector>

#include <ros/init.h>
#include <ros/ros.h>
#include <ros/spinner.h>

int main(int argc, char** argv) {
  std::cout << "Hello, Ros Param!" << std::endl;
  ros::init(argc, argv, "test_param_node");
  ros::NodeHandle nh;

  const std::string topic = "/hmh/test_param";
  const int a = 1;
  const double b = 3.14;
  const std::vector<float> c = {1, 2, 3, 4, 5, 6};

  {
    std::cout << "@@@@@ UUID @@@@@@" << std::endl;
    std::string t;
    nh.getParam("/run_id", t);
    std::cout << "uuid: " << t << std::endl;
  }

  {
    std::cout << "@@@@@ 设置int参数 @@@@@@" << std::endl;
    nh.setParam(topic, a);
  }

  {
    std::cout << "@@@@@ 获取int参数 @@@@@@" << std::endl;
    int t = 0;
    nh.getParam(topic, t);
    assert(t == a);
  }
  {
    std::cout << "@@@@@ 获取int参数失败, 设置默认值 @@@@@@" << std::endl;
    int t = -1;
    nh.getParam("x", t);
    assert(t == -1);
  }

  {
    std::cout << "@@@@@ 设置std::vector参数 @@@@@@" << std::endl;
    nh.setParam(topic, c);
  }

  {
    std::cout << "@@@@@ 获取std::vector参数 @@@@@@" << std::endl;
    std::vector<float> t;
    nh.getParam(topic, t);
    assert(t.size() == c.size());
    for (int i = 0; i < t.size(); i++) {
      assert(t.at(i) == c.at(i));
    }
  }

  return 0;
}
