#include <unistd.h>

#include <chrono>
#include <iostream>

#include "singleton.hpp"

struct Cat {
 public:
  Cat() {
    std::chrono::system_clock::time_point tp =
        std::chrono::system_clock().now();
    time_t tm = std::chrono::system_clock::to_time_t(tp);
    borth_ = ctime(&tm);
  }
  std::string name() const { return name_; }
  std::string borth() const { return borth_; }

 private:
  std::string name_ = "tom";
  std::string borth_;
};

int main(int argc, char* argv[]) {
  auto cat1 = Singleton::Instance<Cat>();  // Tue Dec 20 16:33:54 2022
  // Cat* cat1 = new Cat(); // Tue Dec 20 16:33:41 2022
  sleep(2);
  auto cat2 = Singleton::Instance<Cat>();  // Tue Dec 20 16:33:54 2022
  // Cat* cat2 = new Cat(); Tue Dec 20 16:33:43 2022

  std::cout << "cat1 borth: " << cat1->borth() << std::endl;
  std::cout << "cat2 borth: " << cat2->borth() << std::endl;

  return 0;
}
