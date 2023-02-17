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

  /// 独享指针(两个指针不能指向一个对象，不能进行复制操作只能进行移动操作)
  // 移动(std::move()): 移动不会构造新的对象
  // 我有一本书
  //   拷贝: 手抄书的内容给你, 出现两本一模一样的书
  //   移动: 我把书给你, 不会出现新的书, 但是我没有了书的管理权
  {
    std::unique_ptr<Cat> cat = std::make_unique<Cat>("Unique Tom");
    assert(cat->name() == "Unique Tom");
    assert(cat != nullptr);
    // // std::unique_ptr<Cat> cat2 = cat; // error
    // // auto cat2 = cat;  // error
    std::unique_ptr<Cat> cat2 = std::move(cat);
    assert(cat2 != nullptr);
    assert(cat == nullptr);
  }
  {
    // std::shared_ptr -> std::unique_ptr  not ok
    // std::unique_ptr -> std::shared_ptr  ok

    // not ok
    // std::shared_ptr<Cat> s_cat = std::make_shared<Cat>();
    // std::unique_ptr<Cat> u_cat = std::move(s_cat);

    // ok
    std::unique_ptr<Cat> u_cat = std::make_unique<Cat>();
    std::shared_ptr<Cat> s_cat = std::move(u_cat);
  }

  /// 弱智能指针
  {
    std::shared_ptr<Cat> cat = std::make_shared<Cat>("Tom");
    assert(cat.use_count() == 1);
    std::shared_ptr<Cat> cat2 = cat;
    assert(cat.use_count() == 2);
    std::weak_ptr<Cat> weak_cat = cat;  // 不增加引用计数
    assert(cat.use_count() == 2);
    // 使用: ptr->lock()
    assert(weak_cat.lock() != nullptr);
    assert(weak_cat.lock()->name() == "Tom");
  }

  /// 智能void类型指针
  {
    std::shared_ptr<void> void_cat = std::make_shared<Cat>("Tom");
    assert(void_cat.use_count() == 1);
    std::shared_ptr<Cat> cat = std::static_pointer_cast<Cat>(void_cat);
    assert(cat->name() == "Tom");
    assert(void_cat.use_count() == 2);
    assert(cat.use_count() == 2);
    void_cat.reset();
    assert(void_cat.use_count() == 0);
    assert(cat != nullptr);
    if (cat) {
      std::cout << "xxx" << cat.use_count() << std::endl;
    }
  }
  return 0;
}
