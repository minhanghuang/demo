#include <iostream>
#include <stdio.h>

int main(int argc, char *argv[]) {
  // const char *p = "123456";
  // // char *p;
  // if (p == NULL) {
  //   printf("空");
  // } else {
  //   printf("不为空");
  //   return 0;
  // }


  // std::string s;
  std::string s = "1234";
  const char *p = s.c_str();
  if (p == NULL) {
    printf("空");
  } else {
    printf("不为空");
    return 0;
  }

}
