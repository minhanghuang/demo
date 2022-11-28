#include <iostream>
#include <queue>
#include <set>
#include <unordered_set>

struct Node {
  double s = 0.;
  double a = 0.;
  std::string name;
  // Node加入std::set必须加上这个重载
  bool operator<(const Node& obj) const { return s < obj.s; }
};

int main(int argc, char* argv[]) {
  std::cout << "C++ Set demo" << std::endl;
  /// set
  std::set<int> int_set;
  for (int i = 10; i > 0; i--) {
    int_set.insert(i);
    std::cout << "  insert:" << i << std::endl;
  }

  int_set.insert(-1);

  std::cout << "set排序(不按顺序存储)" << std::endl;
  for (auto it : int_set) {
    std::cout << "  " << it << std::endl;
  }
  std::cout << "set排序" << std::endl;

  /// set struct
  std::set<Node> ns;
  Node n1{11, 1, "1"};
  Node n2{14, 1, "2"};
  Node n3{15, 1, "3"};
  Node n5{19, 1, "5"};
  Node n4{17, 1, "4"};
  ns.insert(n1);
  ns.insert(n2);
  ns.insert(n3);
  ns.insert(n5);
  ns.insert(n4);
  for (const auto& n : ns) {
    std::cout << "n: " << n.s << std::endl;
  }
  Node nx{19, 1, "nx"};
  // auto ns_ret = ns.upper_bound(nx); // 第一个大于19的元素
  auto ns_ret = ns.lower_bound(nx); // 第一个大于等于19的元素
  if (ns_ret == ns.end()) {
    std::cout << "没找到." << std::endl;
  } else {
    std::cout << "找到: " << (*ns_ret).s << std::endl;
  }

  /// unordered_set
  std::unordered_set<int> int_unset;
  for (int i = 10; i > 0; i--) {
    int_unset.insert(i);
    std::cout << "  insert:" << i << std::endl;
  }

  int_unset.insert(-1);
  int_unset.insert(-99);
  int_unset.insert(99);

  std::cout << "unset排序" << std::endl;
  for (auto it : int_unset) {
    std::cout << "  " << it << std::endl;
  }
  std::cout << "unset排序" << std::endl;

  return 0;
}
