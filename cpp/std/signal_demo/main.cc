#include <csignal>
#include <cstdlib>
#include <iostream>
#include <thread>

void SignalHandler(int signum) {
  std::cout << "signum: " << signum << std::endl;
  std::exit(signum);
}

class MyClass {
 public:
  MyClass() = default;
  ~MyClass() = default;
  static void Quit() { std::cout << "Quit" << std::endl; }
  void Quit2() { std::cout << "Quit2" << std::endl; }

 private:
};

void CatchSignals(std::initializer_list<int> signals) {
  std::cout << "CatchSignals start" << std::endl;
  auto handler = [](int sig) -> void { MyClass::Quit(); };
  sigset_t blockingMask;
  sigemptyset(&blockingMask);
  for (auto sig : signals) {
    // std::cout << "signal: " << sig << std::endl;
    sigaddset(&blockingMask, sig);
  }
  struct sigaction sa;
  sa.sa_handler = handler;
  sa.sa_mask = blockingMask;
  sa.sa_flags = 0;
  for (const auto& sig : signals) {
    sigaction(sig, &sa, nullptr);
  }
  std::cout << "CatchSignals end" << std::endl;
}

int main(int argc, char* argv[]) {
  std::cout << "Hello, signal" << std::endl;

  {
      // std::cout << "@@@@@ 中断 @@@@@" << std::endl;
      // std::signal(SIGINT, SignalHandler);   // Ctrl+C
      // std::signal(SIGSEGV, SignalHandler);  // 捕获段错误
      // std::signal(SIGABRT, SignalHandler);  // 捕获中止信号

      // for (int i = 0; i < 10; i++) {
      //   std::cout << "i: " << i << std::endl;
      // }

      // std::abort();  // 异常终止
  }

  {
    std::cout << "@@@@@ 中断 @@@@@" << std::endl;
    CatchSignals({SIGQUIT, SIGSEGV, SIGABRT, SIGINT, SIGTERM, SIGHUP});
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::abort();  // 异常终止
  }

  std::cout << "end" << std::endl;
  return 0;
}
