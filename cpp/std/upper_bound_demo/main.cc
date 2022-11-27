#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct Poly3 {
  double s = 0.;
  double a = 0.;
  double b = 0.;
};

int main(int argc, char* argv[]) {
  std::cout << "Hello upper_bound." << std::endl;
  /// vector
  std::vector<int> a{11, 12, 13, 15, 16, 17, 18, 111};
  // 从数组的begin位置到end-1位置二分查找第一个大于num的数字，找到返回该数字的地址，不存在则返回end
  auto a_ret =
      std::upper_bound(a.begin(), a.end(), 14);  // lower_bound: 第一个大于等于
  if (a_ret == a.end()) {
    std::cout << "没找到." << std::endl;
  } else {
    std::cout << "找到: " << a.at(a_ret - a.begin()) << std::endl;
  }
  a_ret = std::upper_bound(a.begin(), a.end(), 123);
  if (a_ret == a.end()) {
    std::cout << "没找到." << std::endl;
  } else {
    std::cout << "找到: " << a.at(a_ret - a.begin()) << std::endl;
  }

  /// set
  std::set<int> s{11, 12, 13, 15, 16, 17, 18, 111};
  auto s_ret = s.upper_bound(14);
  if (s_ret == s.end()) {
    std::cout << "没找到." << std::endl;
  } else {
    std::cout << "找到: " << *s_ret << std::endl;
  }

  return 0;
}
