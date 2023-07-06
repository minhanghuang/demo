#include <future>
#include <iostream>
#include <map>
#include <thread>
#include <vector>

class Animal {
 public:
  Animal() = default;
  int Eat() {
    std::cout << "eat" << std::endl;
    for (int i = 0; i < 3; i++) {
      future_map_.insert(
          {i, std::async(std::launch::async, [&] { return task(i); })});
    }
    for (int i = 0; i < 4; i++) {
      std::cout << "################" << i << std::endl;
      // 判断task是否已经存在
      if (future_map_.count(i)) {
        // 判断task运行状态
        if (std::future_status::ready ==
            future_map_.at(i).wait_for(std::chrono::seconds(0))) {
          std::cout << "任务完成, 创建新任务" << std::endl;
          future_map_.insert({i, std::async(std::launch::async,
                                            [&] { return task(i * 10); })});
        } else {
          std::cout << "上一次任务未完成" << std::endl;
        }
      } else {
        std::cout << "创建新任务" << std::endl;
        future_map_.insert(
            {i, std::async(std::launch::async, [&] { return task(i * 10); })});
      }
    }
    return 0;
  }

 private:
  std::map<int, std::future<int>> future_map_;
  int task(int value) {
    std::cout << "task " << value << " start\n" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "task " << value << " done\n" << std::endl;
    return 0;
  }
};

int main(int argc, char* argv[]) {
  Animal animal;
  animal.Eat();
  return 0;
}
