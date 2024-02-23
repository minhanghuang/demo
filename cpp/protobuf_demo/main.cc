#include <iostream>

#include <google/protobuf/timestamp.pb.h>

#include "proto/hello.pb.h"

int main(int argc, char* argv[]) {
  std::cout << "Hello, Protobuf!" << std::endl;

  {
    std::cout << "repeated 赋值" << std::endl;
    Person person = Person();
    person.add_hobbies("baseball");
    person.add_hobbies("football");
    std::cout << "person : \n" << person.DebugString() << std::endl;
  }
  return 0;
}
