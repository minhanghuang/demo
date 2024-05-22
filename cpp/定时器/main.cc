#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

class Timer {
 public:
  Timer() = default;
  ~Timer() { StopAll(); }

  void Register(std::chrono::milliseconds duration,
                std::function<void()> callback) {
    std::shared_ptr<std::atomic<bool>> running =
        std::make_shared<std::atomic<bool>>(true);

    std::thread thread([duration, callback, running]() {
      while (*running) {
        std::this_thread::sleep_for(duration);
        if (*running) callback();
      }
    });

    {
      std::lock_guard<std::mutex> guard(mutex_);
      threads_.emplace_back(std::move(thread));
      running_flags_.emplace_back(running);
    }
  }

 private:
  void StopAll() {
    for (auto& running : running_flags_) {
      *running = false;
    }
    for (auto& thread : threads_) {
      if (thread.joinable()) {
        thread.join();
      }
    }
    threads_.clear();
    running_flags_.clear();
  }

  std::mutex mutex_;
  std::vector<std::thread> threads_;
  std::vector<std::shared_ptr<std::atomic<bool>>> running_flags_;
};

int main() {
  std::cout << "周期性定时器启动" << std::endl;
  Timer timer;

  timer.Register(std::chrono::milliseconds(200), []() {
    std::cout << "定时器1触发: 每200ms执行一次" << std::endl;
  });

  timer.Register(std::chrono::milliseconds(300), []() {
    std::cout << "定时器2触发: 每300ms执行一次" << std::endl;
  });

  while (true)
    ;

  return 0;
}
