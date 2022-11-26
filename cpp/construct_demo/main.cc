#include <iostream>
#include <memory>
#include <string>
#include <utility>

struct Cat {
  Cat() = default;
  Cat(const Cat& cat) {  // 拷贝构造函数
    std::cout << "Copy Construct." << std::endl;
    name = "copy_" + cat.name;
  }
  Cat(Cat&& cat) {  // 移动构造函数
    std::cout << "Move Construct." << std::endl;
    name = "move_" + cat.name;
  }
  Cat& operator=(const Cat& cat) {
    std::cout << "= Construct." << std::endl;
    name = "Operator_" + cat.name;
    return *this;
  }
  std::string name;
  int age = 0;
  void Print() {
    std::cout << "name: " << name << std::endl;
    std::cout << "age: " << age << std::endl;
  }
};

int main(int argc, char* argv[]) {
  std::cout << "Hello construct." << std::endl;
  Cat cat;
  cat.name = "Tom";
  cat.age = 1;
  cat.Print();
  std::shared_ptr<Cat> copy_cat = std::make_shared<Cat>(cat);
  copy_cat->Print();
  std::shared_ptr<Cat> move_cat = std::make_shared<Cat>(std::move(cat));
  move_cat->Print();
  Cat copy_cat2 = cat;  // 等价: Cat copy_cat2(cat);
  copy_cat2.Print();
  Cat copy_cat3;
  copy_cat3 = cat; // 重载=
  copy_cat3.Print();
  return 0;
}
