#include <unistd.h>

#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "macros.h"
#include "singleton.hpp"

struct Animal {
 public:
  Animal() {
    std::chrono::system_clock::time_point tp =
        std::chrono::system_clock().now();
    time_t tm = std::chrono::system_clock::to_time_t(tp);
    borth_ = ctime(&tm);
  }
  std::string borth() const { return borth_; }

 private:
  std::string borth_;
};

struct Cat : public Animal {
 public:
  Cat() : Animal() {}
};

struct Dog : public Animal {
 public:
  Dog() : Animal() {}
};

class Mouse : public Animal {
 public:
  DECLARE_SINGLETON(Mouse)
};

Mouse::Mouse() {}

int main(int argc, char* argv[]) {
  {
    std::cout << "function singleton" << std::endl;
    auto cat1 = Singleton<Cat>::Instance();  // Tue Dec 20 16:33:54 2022
    assert(cat1 != nullptr);
    // Cat* cat1 = new Cat(); // Tue Dec 20 16:33:41 2022
    std::this_thread::sleep_for(std::chrono::seconds(2));
    auto cat2 = Singleton<Cat>::Instance();  // Tue Dec 20 16:33:54 2022
    assert(cat2 != nullptr);
    // Cat* cat2 = new Cat(); Tue Dec 20 16:33:43 2022

    auto dog1 = Singleton<Dog>::Instance();  // Tue Dec 20 16:33:56 2022
    assert(dog1 != nullptr);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    auto dog2 = Singleton<Dog>::Instance();  // Tue Dec 20 16:33:56 2022
    assert(dog2 != nullptr);

    std::cout << "cat1 borth: " << cat1->borth() << std::endl;
    std::cout << "cat2 borth: " << cat2->borth() << std::endl;
    std::cout << "dog1 borth: " << dog1->borth() << std::endl;
    std::cout << "dog2 borth: " << dog2->borth() << std::endl;

    assert(cat1->borth() == cat1->borth());
    assert(dog1->borth() == dog1->borth());
  }

  {
    std::cout << "macros singleton" << std::endl;
    auto mouse1 = Mouse::Instance();
    assert(mouse1 != nullptr);
    std::this_thread::sleep_for(std::chrono::seconds(2));

    auto mouse2 = Mouse::Instance();
    assert(mouse2 != nullptr);

    std::cout << "mouse1 borth: " << mouse1->borth() << std::endl;
    std::cout << "mouse2 borth: " << mouse2->borth() << std::endl;

    assert(mouse1->borth() == mouse2->borth());
  }
  return 0;
}
