#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>
#include <vector>

bool IsTimePastPeriod(std::chrono::system_clock::time_point t,
                      std::chrono::duration<int> duration) {
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
  std::chrono::duration<double> diff = now - t;
  return diff > duration;
}

int main(int argc, char* argv[]) {
  std::cout << "Hello Time." << std::endl;

  {
    std::cout << "@@@@@ 时间差 @@@@@" << std::endl;
    std::chrono::system_clock::time_point start =
        std::chrono::system_clock::now();
    std::vector<int> tmp1;
    for (int i = 0; i < 10000; i++) {
      tmp1.emplace_back(1);
    }
    std::chrono::system_clock::time_point end =
        std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "1. 时间差: " << diff.count() << "s" << std::endl;
  }

  {
    std::cout << "@@@@@ 默认值 @@@@@" << std::endl;
    std::chrono::system_clock::time_point default_time;  // 1970-01-01 00:00:01
    std::chrono::system_clock::time_point now =
        std::chrono::system_clock::now();
    std::chrono::duration<double> diff = now - default_time;
    std::cout << "时间差: " << diff.count() << "s(当前时间的时间戳)"
              << std::endl;
  }

  {
    std::cout << "@@@@@ 超时 @@@@@" << std::endl;
    // 获取当前时间
    std::chrono::system_clock::time_point target_time =
        std::chrono::system_clock::now();
    // 延时2秒
    std::this_thread::sleep_for(std::chrono::seconds(2));
    auto ret = IsTimePastPeriod(target_time, std::chrono::seconds(1));
    if (ret) {
      std::cout << "超时" << std::endl;  // 超时
    } else {
      std::cout << "未超时" << std::endl;
    }
    ret = IsTimePastPeriod(target_time, std::chrono::seconds(5));
    if (ret) {
      std::cout << "超时" << std::endl;
    } else {
      std::cout << "未超时" << std::endl;  // 未超时
    }
  }

  return 0;
}
