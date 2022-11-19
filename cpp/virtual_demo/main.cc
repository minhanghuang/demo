#include <iostream>

class Animal {
 public:
  Animal() { std::cout << "Animal" << std::endl; }
  virtual ~Animal() = default;
  virtual std::string name() const { return name_; }
  virtual int age() const { return age_; }
  virtual void set_name(const std::string& name) { name_ = name; }
  virtual void set_age(int age) { age_ = age; }
  void eat() { std::cout << "Animal eat." << std::endl; }

 protected:
  std::string name_;
  int age_ = 0;
};

class Cat : public Animal {
 public:
  Cat() { std::cout << "Cat" << std::endl; }
  virtual void set_name(const std::string& name) { name_ = name + "_Cat"; }
  void eat() { std::cout << "Cat eat." << std::endl; }
  void miao() { std::cout << "Cat miao." << std::endl; }
};

/// g++ -std=c++11 main.cc -o main
int main(int argc, char* argv[]) {
  std::cout << "virtual" << std::endl;

  /// Animal Pointer
  std::cout << "---- 1 ----" << std::endl;
  Animal* a_ptr = new Cat();
  a_ptr->set_name("Tom");
  std::cout << "name: " << a_ptr->name() << std::endl; // Tom_Cat
  a_ptr->eat();  // Animal eat.
  // a_ptr->miao();  // error
  delete a_ptr;

  std::cout << "---- 2 ----" << std::endl;
  Cat* b_ptr = new Cat();
  b_ptr->set_name("Tom");
  std::cout << "name: " << b_ptr->name() << std::endl; // Tom_Cat
  b_ptr->eat();   // Cat eat.
  b_ptr->miao();  // Cat miao
  delete b_ptr;

  return 0;
}
