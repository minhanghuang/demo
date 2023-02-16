#include <cassert>
#include <iostream>
#include <memory>
#include <mutex>
#include <utility>

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
  Cat(const std::string& name) {
    name_ = name;
    std::cout << name_ << " Cat Construct" << std::endl;
  }
  ~Cat() { std::cout << name_ << " Cat Destruct" << std::endl; }
  void set_name(const std::string& name) { name_ = name; }
  const std::string& feature() const { return feature_; }

 private:
  std::string feature_ = "miao~";
};

int main(int argc, char* argv[]) {
  std::cout << "Hello, Pointer." << std::endl;

  // 普通指针
  {
    Cat* cat = new Cat();
    assert(cat->name() == "animal");
    cat->set_name("Tom");
    assert(cat->name() == "Tom");
    delete cat;
  }

  // 万能指针
  {
    Cat* cat = new Cat();
    void* void_cat = cat;  // 普通指针转void*不需要强制类型转换
    free(void_cat);        // void* 使用free()释放内存
  }
  {
    void* void_cat = new Cat();
    // dynamic_cast只能用于具有继承关系的指针
    Cat* cat = static_cast<Cat*>(void_cat);
    assert(cat->name() == "animal");
  }

  /// 智能指针
  // 共享指针
  // std::shared_ptr<Cat> cat = new Cat();  // error
  {
    std::shared_ptr<Cat> cat(new Cat());
    assert(cat->name() == "animal");
  }
  {
    std::shared_ptr<Cat> cat = std::make_shared<Cat>();
    assert(cat->name() == "animal");
  }
  {
    std::shared_ptr<Cat> cat = std::make_shared<Cat>();
    assert(cat.use_count() == 1);
    std::shared_ptr<Cat> cat2 = cat;
    assert(cat.use_count() == 2);
    cat2.reset();
    assert(cat.use_count() == 1);
  }

  // 独享指针(两个指针不能指向一个对象，不能进行复制操作只能进行移动操作)
  // 移动(std::move()): 移动不会构造新的对象
  {
    std::unique_ptr<Cat> cat = std::make_unique<Cat>("Unique Tom");
    assert(cat->name() == "Unique Tom");
    assert(cat != nullptr);
    // std::unique_ptr<Cat> cat2 = cat; // error
    // auto cat2 = cat;  // error
    std::unique_ptr<Cat> cat2 = std::move(cat);
    assert(cat2 != nullptr);
    assert(cat == nullptr);
  }
  return 0;
}
