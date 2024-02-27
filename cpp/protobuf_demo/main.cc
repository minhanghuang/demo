#include <cassert>
#include <iostream>

#include <google/protobuf/timestamp.pb.h>
#include <google/protobuf/util/time_util.h>

#include "proto/hello.pb.h"

int main(int argc, char* argv[]) {
  std::cout << "Hello, Protobuf!" << std::endl;

  {
    std::cout << "repeated 赋值" << std::endl;
    Person person = Person();
    auto current_time = google::protobuf::util::TimeUtil::GetCurrentTime();
    person.mutable_birth_date()->set_seconds(current_time.seconds());
    person.mutable_birth_date()->set_nanos(0);
    person.add_hobbies("baseball");
    person.add_hobbies("football");
    std::cout << "person : \n" << person.DebugString() << std::endl;
  }

  {
    std::cout << "repeated 取值" << std::endl;
    Person person = Person();
    auto current_time = google::protobuf::util::TimeUtil::GetCurrentTime();
    person.mutable_birth_date()->set_seconds(current_time.seconds());
    person.mutable_birth_date()->set_nanos(0);
    person.add_hobbies("baseball");
    person.add_hobbies("football");

    assert("baseball" == person.hobbies()[0]);
    assert("football" == person.hobbies()[1]);
    assert("baseball" == person.hobbies(0));
    assert("football" == person.hobbies(1));
    std::cout << "hobby 0: " << person.hobbies()[0] << std::endl;
    std::cout << "hobby 1: " << person.hobbies()[1] << std::endl;
    std::cout << "hobby 0: " << person.hobbies(0) << std::endl;
    std::cout << "hobby 1: " << person.hobbies(1) << std::endl;
  }
  return 0;
}
