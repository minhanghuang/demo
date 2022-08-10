#include <cstddef>
#include <iostream>
#include <string>

class Animal {
public:
  ~Animal() = default;
  explicit Animal(const std::string &name) : name_(name) {}
  std::string GetName() { return name_; }
  size_t GetAge() { return age_; }

private:
  // 如果有初始化列表，构造函数直接使用初始化列表的值，将不会选择类中初始化的值
  // 如果没有初始化列表，构造函数将选择类中初始化的值
  // 初始化顺序是按照类中出现的顺序，即先初始化name_，再初始化age_
  std::string name_;
  size_t age_ = 9;
};

class Cat : public Animal {
public:
  ~Cat() = default;
  Cat(const std::string &name) : Animal(name) {}
};

int main(int argc, char *argv[]) {
  std::cout << "class demo" << std::endl;
  Cat cat("Tom");
  std::cout << "cat name:" << cat.GetName() << std::endl;
  std::cout << "cat age:" << cat.GetAge() << std::endl;
  return 0;
}
