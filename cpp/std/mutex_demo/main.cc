#include <iostream>
#include <mutex>

int main(int argc, char* argv[]) {
  std::cout << "Hello, Mutex." << std::endl;
  std::mutex mutex;

  for (int i = 0; i < 10; i++) {
    std::cout << "i: " << i << std::endl;
  }
  return 0;
}
