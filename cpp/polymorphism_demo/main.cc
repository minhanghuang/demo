#include <iostream>
#include <memory>

class Animal {
public:
  Animal() {}
  ~Animal() { std::cout << "~Animal" << std::endl; }
  void Run() { std::cout << "Animal Run ..." << std::endl; }
  virtual void Eat() { std::cout << "Animal Eat ..." << std::endl; }
};

class Cat : public Animal {
public:
  Cat() {}
  ~Cat() { std::cout << "~Cat" << std::endl; }
  void Run() { std::cout << "Cat Run ..." << std::endl; }
  // virtual 可有可无, 推荐加上
  virtual void Eat() { std::cout << "Cat Eat ..." << std::endl; }
  void Jump() { std::cout << "Cat Jump ." << std::endl; }
};

class Dog : public Animal {
public:
  Dog() {}
  ~Dog() { std::cout << "~Dog" << std::endl; }
  void Run() { std::cout << "Dog Run ..." << std::endl; }
  // virtual 可有可无, 推荐加上
  virtual void Eat() { std::cout << "Dog Eat ..." << std::endl; }
};

int main(int argc, char *argv[]) {
  std::cout << "C++ 多态" << std::endl;

  // std::shared_ptr<Animal> a = std::make_shared<Animal>();
  // std::shared_ptr<Cat> c = std::make_shared<Cat>();
  // a->Run(); // Animal Run ...
  // c->Run(); // Cat Run ...

  // 非多态
  // std::shared_ptr<Animal> c = std::make_shared<Cat>();
  // std::shared_ptr<Animal> d = std::make_shared<Dog>();
  // c->Run(); // Animal Run ...
  // d->Run(); // Animal Run ...

  // // 多态; 编译器会调用指针指向对象的虚函数，而与指针的类型无关
  // std::shared_ptr<Animal> c = std::make_shared<Cat>();
  // std::shared_ptr<Animal> d = std::make_shared<Dog>();
  // c->Jump(); // error 
  // c->Eat(); // Cat Eat ...
  // d->Eat(); // Dog Eat ...

  return 0;
}
