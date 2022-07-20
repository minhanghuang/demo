#include <cstddef>
#include <functional>
#include <iostream>

struct Data {
  std::string name;
  size_t age;
};

bool CallBack1(int a, int b) {
  std::cout << "callback1: " << a << "-" << b << std::endl;
  return true;
}

class CallBack {
public:
  ~CallBack() = default;
  CallBack() = default;
  void Get(int a, int b) {
    std::cout << "CallBack Get:" << a << "-" << b << std::endl;
  }
  void Get2(int a, int b, Data* data) {
    std::cout << "CallBack Get2:" << a << "-" << b << "-" << data->name << std::endl;
  }
};

int main(int argc, char *argv[]) {
  std::cout << "function demo" << std::endl;
  Data data;
  data.name = "haha";
  data.age = 19;

  // 1. simple
  std::function<bool(int, int)> callback1 = CallBack1;
  callback1(2, 5);

  // 2. 类方法
  CallBack cb;
  std::function<void(int, int)> callback2 = std::bind(
      &CallBack::Get, &cb, std::placeholders::_1, std::placeholders::_2);
  callback2(2, 7);

  std::function<void(int, int)> callback3 = std::bind(
      &CallBack::Get2, &cb, std::placeholders::_1, std::placeholders::_2, &data);
  callback3(2, 7);

  return 0;
}
