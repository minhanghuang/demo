#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Animal {
public:
  ~Animal() = default;
  Animal(const std::string &n) { name = n; }
  void Eat() const { std::cout << "Animal Eat" << std::endl; }
  void SetName(const std::string &n) { name = n; }
  std::string GetName() { return name; }
  std::string name;
};

std::shared_ptr<Animal> GetPtr() {
  std::shared_ptr<Animal> ptr = std::make_shared<Animal>("g");
  std::cout << "ptr addr:" << ptr << std::endl;
  return ptr;
}

std::shared_ptr<const Animal> GetConstPtr() {
  // std::shared_ptr<Animal> GetConstPtr() {
  std::shared_ptr<Animal> ptr = std::make_shared<Animal>("g");
  std::cout << "ptr addr:" << ptr << std::endl;
  return ptr;
}

int main(int argc, char *argv[]) {
  std::cout << "ptr demo" << std::endl;

  // 1. const
  int *p = new int(0);
  // 1.1 常量指针; 不能修改指针所指向的内存, 可以修改指针的指向
  const int *p1 = new int(1);
  // // *p1 = 2; // error
  // // p1 = p; // ok

  // 1.2 指针常量; 可以修改指针指向的内存, 不可以修改指针的指向
  int *const p2 = new int(2);
  // // *p2 = 22; // ok
  // // p2 = p; // error

  // 1.3 既不能修改指针指向的内存, 也不能修改指针的指向
  const int *const p3 = new int(3);
  // // *p3 = 33; // error
  // // p3 = p; // error

  delete p;
  delete p1;
  delete p2;
  delete p3;

  // 2. shared_ptr, unique_ptr, weak_ptr, auto_ptr
  // 2.1 const
  // shared_ptr<T> p;             ---> T * p; : nothing is const const
  // shared_ptr<T> p;       ---> T * const p;                              : p
  // is const shared_ptr<const T> p;       ---> const T * p;       <=> T const *
  // p;       : *p is const const shared_ptr<const T> p; ---> const T * const p;
  // <=> T const * const p; : p and *p are const.

  std::shared_ptr<Animal> a0 = std::make_shared<Animal>("a");
  const std::shared_ptr<Animal> a1 = std::make_shared<Animal>("a1");
  // a1->name = "A1"; // ok
  // // a1 = a; // error
  // a0.swap(a1); // error
  a1->SetName("A1");

  std::shared_ptr<const Animal> a2 = std::make_shared<Animal>("a2");
  // // a2->name = "A1"; // error
  // a2 = a0; // ok
  // a0.swap(a2); // error
  // 2.2 swap

  // std::shared_ptr<Animal> a3 = std::make_shared<Animal>("a3");
  // std::cout << "a3 addr:" << a3 << std::endl;
  // std::cout << "a0 addr:" << a0 << std::endl;
  // std::cout << "a0 name:" << a0->name << std::endl;
  // std::cout << "a3 name:" << a3->name << std::endl;
  // a3.swap(a0); // 指针指向的内存地址互换
  // std::cout << "---" << std::endl;
  // std::cout << "a3 addr:" << a3 << std::endl;
  // std::cout << "a0 addr:" << a0 << std::endl;
  // std::cout << "a0 name:" << a0->name << std::endl;
  // std::cout << "a3 name:" << a3->name << std::endl;

  // std::cout << "addr:" << GetPtr() << std::endl;

  // auto ptr = GetConstPtr();
  // ptr->Eat();
  // std::cout << "const ptr:" << ptr << std::endl;

  // // vector ptr -> vector const ptr
  // std::vector<std::shared_ptr<const Animal>> vp;
  // for (int i = 0; i < 3; i++) {
  //   auto pi = std::make_shared<Animal>("a1");
  //   std::cout << "pi addr: " << pi << std::endl;
  //   vp.emplace_back(pi);
  // }
  // std::cout << "---" << std::endl;
  // for (const auto &pi : vp) {
  //   std::cout << "p addr: " << pi << std::endl;
  // }

  // std::vector<const std::shared_ptr<const Animal>> vp;
  // for (int i = 0; i < 3; i++) {
  //   auto pi = std::make_shared<Animal>("a1");
  //   std::cout << "pi addr: " << pi << std::endl;
  //   pi->SetName("a" + std::to_string(i));
  //   vp.emplace_back(pi);
  // }
  // std::cout << "---" << std::endl;
  // for (auto &pi : vp) {
  //   std::cout << "p addr: " << pi << " name: " << pi->name << " count: " << pi.use_count() << std::endl;
  //   // pi.SetName(" "); // error
  //   // pi.GetName(); // error, GetName() not const function 
  //   pi->Eat(); // ok
  // }

  return 0;
}
