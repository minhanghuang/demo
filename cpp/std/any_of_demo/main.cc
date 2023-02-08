#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
  std::cout << "Hello STL any_of." << std::endl;

  std::vector<int> vs{1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4};
  int target = 0;

  // std::all_of   全都满足: 返回true
  auto ret =
      std::all_of(vs.begin(), vs.end(), [target](int v) { return target < v; });
  std::cout << "所有的元素都比目标元素大: " << ret << std::endl;

  // std::any_of   全都满足: 返回true
  target = 1;
  ret =
      std::any_of(vs.begin(), vs.end(), [target](int v) { return target < v; });
  std::cout << "至少有一个元素比目标元素大: " << ret << std::endl;

  // std::onoe_of   全都不满足: 返回true
  target = 11;
  ret = std::none_of(vs.begin(), vs.end(),
                     [target](int v) { return target < v; });
  std::cout << "所有元素都不比目标元素大: " << ret << std::endl;
  return 0;
}
