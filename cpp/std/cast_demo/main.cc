#include <iostream>
#include <memory>
#include <string>

class Animal {
 public:
  virtual ~Animal() = default;
  Animal() = default;
  const std::string& name() const { return name_; }
  int age() const { return age_; }

 protected:
  std::string name_ = "animal";
  int age_ = 1;
};

class Cat : public Animal {
 public:
  Cat() { std::cout << "Cat Construct" << std::endl; }
  void set_name(const std::string& name) { name_ = name; }
  const std::string& feature() const { return feature_; }

 private:
  std::string feature_ = "miao~";
};

int main(int argc, char* argv[]) {
  std::cout << "Hello, Cast." << std::endl;

  /// 1. static_cast
  // 普通变量
  int a = 100;
  unsigned int b = 200;
  std::cout << "a: " << a << "  "
            << "b: " << b << std::endl;
  b = static_cast<unsigned int>(a);
  std::cout << "a: " << a << "  "
            << "b: " << b << std::endl;
  // 指针
  {
    // 向下转换
    Animal* animal_cat = new Cat();
    Cat* cat = static_cast<Cat*>(animal_cat);
    assert("miao~" == cat->feature());
    std::cout << "cat feature: " << cat->feature() << std::endl;
  }
  {
    // 向上转换
    Cat* cat = new Cat();
    Animal* animal_cat = static_cast<Animal*>(cat);
    assert("animal" == animal_cat->name());
    std::cout << "animal name: " << animal_cat->name() << std::endl;
  }

  /// 2. dynamic_cast(只在多态的继承关系才有效)
  // a.
  // 将派生类指针转换为基类指针(上行转换),这个操作与static_cast的效果是一样的
  // b.
  // 将基类指针转换为派生类指针(下行转换),dynamic_cast具有类型检查的功能,比static_cast更安全
  //  如果转换的是指针,失败时会返回空指针
  //  如果转换的是引用,会抛出std::bad_cast异常
  {
    // 向下转换
    Animal* animal_cat = new Cat();
    Cat* cat = dynamic_cast<Cat*>(animal_cat);
    assert("miao~" == cat->feature());
    std::cout << "cat feature: " << cat->feature() << std::endl;
  }
  {
    // 向上转换
    Cat* cat = new Cat();
    Animal* animal_cat = dynamic_cast<Animal*>(cat);
    assert("animal" == animal_cat->name());
    std::cout << "animal name: " << animal_cat->name() << std::endl;
  }

  /// 智能指针
  /// 3. std::static_pointer_cast(智能指针的static_cast)
  {
    std::shared_ptr<Animal> animal_cat = std::make_shared<Cat>();
    std::shared_ptr<Cat> cat = std::static_pointer_cast<Cat>(animal_cat);
    assert("miao~" == cat->feature());
    std::cout << "cat feature: " << cat->feature() << std::endl;
  }
  /// 4. std::dynamic_pointer_cast(智能指针的dynamic_cast)
  {
    std::shared_ptr<Animal> animal_cat = std::make_shared<Cat>();
    std::shared_ptr<Cat> cat = std::dynamic_pointer_cast<Cat>(animal_cat);
    assert("miao~" == cat->feature());
    std::cout << "cat feature: " << cat->feature() << std::endl;
  }

  /// void*
  {
    void* n_cat = new Cat();
    Cat* cat = (Cat*)(n_cat);
    assert("miao~" == cat->feature());
    std::cout << "cat feature: " << cat->feature() << std::endl;
  }
  {
    void* n_cat = new Cat();
    Cat* cat = static_cast<Cat*>(n_cat);
    // Cat* cat = dynamic_cast<Cat*>(n_cat); // error
    assert("miao~" == cat->feature());
    std::cout << "cat feature: " << cat->feature() << std::endl;
  }
  {
    void* n_cat = new Cat();
    Cat* cat_1 = static_cast<Cat*>(n_cat);
    cat_1->set_name("Tom");
    // std::shared_ptr<Cat> cat = std::static_pointer_cast<Cat>(n_cat); // error
    // std::shared_ptr<Cat> cat =
    // std::shared_ptr<Cat>(dynamic_cast<Cat*>(n_cat));  // error
    std::shared_ptr<Cat> cat = std::shared_ptr<Cat>(static_cast<Cat*>(n_cat));
    assert("miao~" == cat->feature());
    std::cout << "cat feature: " << cat->feature() << std::endl;
    assert("Tom" == cat->name());
    std::cout << "cat name: " << cat->name() << std::endl;
  }
  {
    void* n_cat = new Cat();
    Cat* cat_1 = static_cast<Cat*>(n_cat);
    cat_1->set_name("Tom");
    std::unique_ptr<Cat> cat = std::unique_ptr<Cat>(static_cast<Cat*>(n_cat));
    assert("miao~" == cat->feature());
    std::cout << "cat feature: " << cat->feature() << std::endl;
    assert("Tom" == cat->name());
    std::cout << "cat name: " << cat->name() << std::endl;
  }
  return 0;
}
