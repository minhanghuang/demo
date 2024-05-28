#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>  // 随机数

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

  {
    std::cout << "repeated 排序" << std::endl;
    // 生成随机数匿名函数
    auto generate_random_number = []() {
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dis(-20, 50);
      return dis(gen);
    };

    Person person = Person();
    for (int i = 0; i < 10; i++) {
      auto interest = person.add_interests();
      interest->set_level(generate_random_number());
    }

    // 排序
    std::sort(person.mutable_interests()->begin(),  // 必须是mutable_
              person.mutable_interests()->end(),    // 必须是mutable_
              [](const Interest& v1, const Interest& v2) {
                return v1.level() < v2.level();
              });

    for (const auto& interest_pb : person.interests()) {
      std::cout << "level: " << interest_pb.level() << std::endl;
    }
    /*
      level: -19
      level: -3
      level: -2
      level: 0
      level: 1
      level: 27
      level: 33
      level: 35
      level: 39
      level: 43
     **/
  }

  {
    std::cout << "repeated 添加" << std::endl;
    {
      Person person = Person();
      for (int i = 0; i < 10; i++) {
        auto interest = person.add_interests();
        interest->set_level(i);
      }
      std::cout << "person: " << person.DebugString() << std::endl;
    }
    {
      Person person = Person();
      Interest interest;
      interest.set_level(1);
      *person.mutable_interests()->Add() = interest;
      std::cout << "person: " << person.DebugString() << std::endl;
    }
  }

  return 0;
}
