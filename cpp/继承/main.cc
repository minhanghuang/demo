#include <iostream>
#include <string>

class Animal {
 public:
  Animal() = default;

  // 虚析构函数: 允许在派生类中重写(override)该函数
  // 多态性:通过基类指针/引用来删除派生类对象时,如果析构函数不是虚函数,只会调用基类的析构函数,而不会调用派生类的析构函数,导致可能的资源泄漏。
  // 确保正确的析构顺序:当一个派生类对象被删除时,首先会调用该类自身的析构函数,然后依次调用其每个基类的析构函数。虚析构函数可以确保这种调用顺序是正确的。
  // 抽象类:如果一个类包含纯虚函数,那它就是一个抽象类。抽象类应该至少有一个虚函数,通常这个虚函数就是虚析构函数。
  virtual ~Animal() = default;

  // 纯虚函数:
  // 主要目的是实现动态绑定,在运行时根据对象的实际类型来决定调用哪个函数版本。
  // 纯虚函数是一种特殊的虚函数,它没有函数体,也就是说没有定义,必须在派生类中实现。一个包含纯虚函数的类就被称为抽象类。
  // 抽象类不能被实例化(不能创建对象),它只能作为基类,用于派生新的类。
  // 派生类必须重写(override)基类中的纯虚函数,否则它们也将成为抽象类。
  virtual void set_name(const std::string& name) = 0;

  // 没有virtual修饰, 因此在派生类中无法覆盖(override)它
  // std::string name() const { return name_; }

  //  该函数声明为虚函数, 在派生类中可以覆盖(override)该函数,从而实现多态性
  // virtual std::string name() const { return name_; }

  // 不能在任何派生类中被覆盖
  virtual std::string name() const final { return name_; }

 protected:
  std::string name_;
};

class Cat : public Animal {
 public:
  Cat();
};

class BlueCat : public Cat {
 public:
  virtual void set_name(const std::string& name) { name_ = name; }
};

int main(int argc, char* argv[]) {
  std::cout << "Hello C++ 继承" << std::endl;

  {
    std::cout << "--- 虚基类, 不能实例化" << std::endl;
    // Animal animal; // 虚基类
    // Cat cat; // 虚基类(因为没有实现父类的纯虚函数)
  }

  {
    BlueCat tom;
    tom.set_name("Tom");
    std::cout << "name: " << tom.name() << std::endl;
  }
  return 0;
}
