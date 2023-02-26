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
    std::cout << "#################### 1-0 " << std::endl;
    Cat* cat = new Cat();
    assert(cat->name() == "animal");
    cat->set_name("Tom");
    assert(cat->name() == "Tom");
    delete cat;
    std::cout << "#################### 1-0 #######" << std::endl;
  }

  // 万能指针
  {
    std::cout << "#################### 2-0 " << std::endl;
    Cat* cat = new Cat();
    void* void_cat = cat;  // 普通指针转void*不需要强制类型转换
    free(void_cat);        // void* 使用free()释放内存
    std::cout << "#################### 2-0 #######" << std::endl;
  }
  {
    std::cout << "#################### 2-1 " << std::endl;
    void* void_cat = new Cat();
    // dynamic_cast只能用于具有继承关系的指针
    Cat* cat = static_cast<Cat*>(void_cat);
    assert(cat->name() == "animal");
    std::cout << "#################### 2-1 #######" << std::endl;
  }

  /// 智能指针
  // 共享指针
  // std::shared_ptr<Cat> cat = new Cat();  // error
  {
    std::cout << "#################### 3-0 " << std::endl;
    std::shared_ptr<Cat> cat(new Cat());
    assert(cat->name() == "animal");
    std::cout << "#################### 3-0 #######" << std::endl;
  }
  {
    std::cout << "#################### 3-1 " << std::endl;
    std::shared_ptr<Cat> cat = std::make_shared<Cat>();
    assert(cat->name() == "animal");
    std::cout << "#################### 3-1 #######" << std::endl;
  }
  {
    std::cout << "#################### 3-2 " << std::endl;
    std::shared_ptr<Cat> cat = std::make_shared<Cat>();
    assert(cat.use_count() == 1);
    std::shared_ptr<Cat> cat2 = cat;
    assert(cat.use_count() == 2);
    assert(cat2.use_count() == 2);
    cat2.reset();
    assert(cat.use_count() == 1);
    std::cout << "#################### 3-2 #######" << std::endl;
  }
  {
    // 使用计数
    std::cout << "#################### 3-3 " << std::endl;
    Cat* cat = new Cat();
    cat->set_name("new_cat");
    Cat* cat2 = cat;
    assert("new_cat" == cat2->name());
    std::shared_ptr<Cat> s_cat = std::shared_ptr<Cat>(cat);
    s_cat.reset();  // 智能指针计数为0后, 普通指针指向内存不变, 但数据已经被销毁
    // auto name = cat2->name(); // error
    assert(cat == cat2);
    std::cout << "#################### 3-3 #######" << std::endl;
  }
  /// 独享指针(两个指针不能指向一个对象，不能进行复制操作只能进行移动操作)
  // 移动(std::move()): 移动不会构造新的对象
  // 我有一本书
  //   拷贝: 手抄书的内容给你, 出现两本一模一样的书
  //   移动: 我把书给你, 不会出现新的书, 但是我没有了书的管理权
  {
    std::cout << "#################### 4-0 " << std::endl;
    std::unique_ptr<Cat> cat = std::make_unique<Cat>("Unique Tom");
    assert(cat->name() == "Unique Tom");
    assert(cat != nullptr);
    // // std::unique_ptr<Cat> cat2 = cat; // error
    // // auto cat2 = cat;  // error
    std::unique_ptr<Cat> cat2 = std::move(cat);
    assert(cat2 != nullptr);
    assert(cat == nullptr);
    std::cout << "#################### 4-0 #######" << std::endl;
  }

  /// 弱智能指针
  {
    std::cout << "#################### 5-0 " << std::endl;
    std::shared_ptr<Cat> cat = std::make_shared<Cat>("Tom");
    assert(cat.use_count() == 1);
    std::shared_ptr<Cat> cat2 = cat;
    assert(cat.use_count() == 2);
    std::weak_ptr<Cat> weak_cat = cat;  // 不增加引用计数
    assert(cat.use_count() == 2);
    // 使用: ptr->lock()
    assert(weak_cat.lock() != nullptr);
    assert(weak_cat.lock()->name() == "Tom");
    std::cout << "#################### 5-0 #######" << std::endl;
  }

  /// 智能void类型指针
  {
    std::cout << "#################### 6-0 " << std::endl;
    std::shared_ptr<void> void_cat = std::make_shared<Cat>("Tom");
    assert(void_cat.use_count() == 1);
    std::shared_ptr<Cat> cat = std::static_pointer_cast<Cat>(void_cat);
    assert(cat->name() == "Tom");
    assert(void_cat.use_count() == 2);
    assert(cat.use_count() == 2);
    void_cat.reset();
    assert(void_cat.use_count() == 0);
    assert(cat != nullptr);
    std::cout << "#################### 6-0 #######" << std::endl;
  }

  /// copy
  {
    std::cout << "#################### 7-0 " << std::endl;
    // object copy to ptr
    Cat cat;
    cat.set_name("copy_tom");
    Cat* new_cat = new Cat(cat);
    assert(new_cat->name() == "copy_tom");
    std::shared_ptr<Cat> cat_shared_ptr = std::make_shared<Cat>(cat);
    assert(cat_shared_ptr->name() == "copy_tom");
    std::unique_ptr<Cat> cat_unique_ptr = std::make_unique<Cat>(cat);
    assert(cat_unique_ptr->name() == "copy_tom");
    std::cout << "#################### 7-0 #######" << std::endl;
  }

  /// convert
  {
    std::cout << "#################### 8-0 " << std::endl;
    // ptr convert to ptr
    // 共享指针 拷贝到 独享指针: 不可
    // 独享指针 拷贝到 共享指针: 可行

    // std::shared_ptr -> std::unique_ptr  not ok
    // std::unique_ptr -> std::shared_ptr  ok

    // not ok
    // std::shared_ptr<Cat> s_cat = std::make_shared<Cat>();
    // std::unique_ptr<Cat> u_cat = std::move(s_cat);

    // ok
    std::unique_ptr<Cat> u_cat = std::make_unique<Cat>();
    std::shared_ptr<Cat> s_cat = std::move(u_cat);

    // ok
    Cat* cat = new Cat();
    cat->set_name("copy_tom");
    assert(cat->name() == "copy_tom");
    std::unique_ptr<Cat> u_cat2 = std::unique_ptr<Cat>(cat);  // ok
    // 将内存管理权限交给unique后, 该内存不可交给其他指针
    // std::shared_ptr<Cat> s_cat2 = std::shared_ptr<Cat>(cat); // ok
    assert(cat->name() == "copy_tom");
    assert(u_cat2->name() == "copy_tom");
    assert(cat != nullptr);
    std::cout << "#################### 8-0 #######" << std::endl;
  }
  {
    // 普通指针转共享指针
    std::cout << "#################### 8-1 " << std::endl;
    Cat* cat = new Cat("8-0");
    std::shared_ptr<Cat> s_cat = std::shared_ptr<Cat>(cat);
    assert(cat == s_cat.get());

    // 普通指针转独享指针: not
    // std::unique_ptr<Cat> u_cat = std::unique_ptr<Cat>(cat); // not ok
    std::cout << "#################### 8-1 #######" << std::endl;
  }

  // swap
  {
    std::cout << "#################### 9-0 " << std::endl;
    std::shared_ptr<Cat> cat = std::make_shared<Cat>();
    cat->set_name("cat1");
    std::shared_ptr<Cat> cat2 = std::make_shared<Cat>();
    cat2->set_name("cat2");
    cat.swap(cat2);  // 指针指向的内存地址互换
    assert("cat2" == cat->name());
    assert("cat1" == cat2->name());
    std::cout << "#################### 9-0 #######" << std::endl;
  }
  {
    // 禁止互换
    std::cout << "#################### 9-1 " << std::endl;
    const std::shared_ptr<Cat> cat = std::make_shared<Cat>();  // 禁止互换
    // std::shared_ptr<Cat const> cat = std::make_shared<Cat>(); // 禁止互换
    cat->set_name("cat1");
    std::shared_ptr<Cat> cat2 = std::make_shared<Cat>();
    cat2->set_name("cat2");
    // cat.swap(cat2);
    std::cout << "#################### 9-1 #######" << std::endl;
  }

  return 0;
}
