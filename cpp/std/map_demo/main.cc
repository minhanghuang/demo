#include <iostream>
#include <map>
#include <string>
#include <unordered_map>



int main(int argc, char *argv[]) {
  std::cout << "std::map demo" << std::endl;
  std::unordered_map<std::string, int> int_route;
  for (int j = 0; j < 10; j++) {
    int_route[std::to_string(j)] = j; 
  }

  std::cout << "获取值:" << int_route["2"] << std::endl;
  std::cout << "获取值:" << int_route.at("2") << std::endl;
  std::cout << "获取值(不存在):" << int_route["22"] << std::endl;
  std::cout << "获取值(不存在):" << int_route.at("22") << std::endl;

  return 0;
}
