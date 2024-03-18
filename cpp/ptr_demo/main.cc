#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <vector>

class Animal {
 public:
  Animal() = default;
  Animal(const std::string& name) : name_(name){};
  virtual ~Animal() = default;

  void set_name(const std::string& name) { name_ = name; }
  std::string name() { return name_; }

 private:
  std::string name_;
};

class Cat : public Animal {
 public:
  Cat() = default;
  ~Cat() = default;
  Cat(const std::string& name) : Animal(name) {}

  const std::string& sound() const { return sound_; }

 private:
  const std::string sound_ = "喵";
};

class Dog : public Animal {
 public:
  Dog() = default;
  ~Dog() = default;
  Dog(const std::string& name) : Animal(name) {}

  const std::string& sound() const { return sound_; }

 private:
  const std::string sound_ = "汪";
};

int main(int argc, char* argv[]) {
  std::cout << "Hello, Ptr" << std::endl;

  {
    std::cout << "@@@@@ 类型转换 @@@@@" << std::endl;
    std::shared_ptr<Animal> a1 = std::make_shared<Cat>("Tom");
    std::cout << "name: " << a1->name() << std::endl;

    std::shared_ptr<Cat> c1 = std::static_pointer_cast<Cat>(a1);
    std::cout << "name: " << c1->name() << std::endl;
    std::cout << "sound: " << c1->sound() << std::endl;
    c1->set_name("Tom2");

    std::shared_ptr<Cat> c2 = std::dynamic_pointer_cast<Cat>(a1);
    std::cout << "name: " << c2->name() << std::endl;
    std::cout << "sound: " << c2->sound() << std::endl;
  }

  {
    std::cout << "@@@@@ 智能指针深拷贝 @@@@@" << std::endl;
    std::shared_ptr<Cat> tom_cat = std::make_shared<Cat>("Tom");
    assert(tom_cat->name() == "Tom");

    /// copy_cat和tom_cat指向不同的内存
    std::shared_ptr<Cat> copy_cat = nullptr;
    copy_cat = std::make_shared<Cat>(*tom_cat);
    assert(copy_cat->name() == "Tom");
    assert(copy_cat.get() != tom_cat.get());
    std::cout << "copy cat add: " << copy_cat.get() << std::endl;
    std::cout << "tom cat add: " << tom_cat.get() << std::endl;
    copy_cat->set_name("X");
    assert(copy_cat->name() == "X");
    assert(tom_cat->name() == "Tom");

    /// tom_cat_2和tom_cat指向不同的内存
    std::shared_ptr<Cat> tom_cat_2 = tom_cat;
    assert(tom_cat_2->name() == "Tom");
    assert(tom_cat_2.get() == tom_cat.get());
    std::cout << "tom cat 2 add: " << tom_cat_2.get() << std::endl;
    std::cout << "tom cat add: " << tom_cat.get() << std::endl;
    tom_cat_2->set_name("X");
    assert(copy_cat->name() == "X");
    assert(tom_cat->name() == "X");
  }

  return 0;
}
