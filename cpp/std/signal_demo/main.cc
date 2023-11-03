#include <csignal>
#include <cstdlib>
#include <iostream>

void SignalHandler(int signum) {
  std::cout << "signum: " << signum << std::endl;
  std::exit(signum);
}

int main(int argc, char* argv[]) {
  std::cout << "Hello, signal" << std::endl;

  std::signal(SIGINT, SignalHandler);   // Ctrl+C
  std::signal(SIGSEGV, SignalHandler);  // 捕获段错误
  std::signal(SIGABRT, SignalHandler);  // 捕获中止信号

  for (int i = 0; i < 10; i++) {
    std::cout << "i: " << i << std::endl;
  }

  std::abort();  // 异常终止
  std::cout << "end" << std::endl;
  return 0;
}
