#include <cstring>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
  std::cout << "Hello, char" << std::endl;
  {
    std::cout << " ---1 " << std::endl;
    char c = 'a';
    std::cout << "char: " << c << std::endl;
  }

  {
    std::cout << " ---2 " << std::endl;
    // 声明
    char* c = new char[10];
    // 赋值
    for (int i = 0; i < 10; i++) {
      c[i] = 'A' + i;
    }
    // 通过长度遍历
    for (int i = 0; i < strlen(c); i++) {
      std::cout << "strlen c: " << c[i] << std::endl;
    }
    // 通过指针移动遍历
    for (char* i = c; *i != '\0'; i++) {
      std::cout << "point c: " << *i << std::endl;
    }
    delete[] c;
  }

  {
    std::cout << " ---3 " << std::endl;
    std::vector<char> c;
    for (int i = 0; i < 10; i++) {
      c.push_back('A' + i);
    }
    for (int i = 0; i < c.size(); i++) {
      std::cout << c[i] << std::endl;
    }
  }

  {
    std::cout << " ---4 " << std::endl;
    // ok
    // std::vector<char*> cs;
    // cs.push_back(new char[10]);
    // cs.push_back(new char[10]);

    // error
    // std::vector<char*> cs;
    // cs[0] = new char[10];
    // cs[1] = new char[10];

    // ok
    std::vector<char*> cs(2);
    cs[0] = new char[10];
    cs[1] = new char[10];

    for (int i = 0; i < 10; i++) {
      cs[0][i] = 'A' + i;
      cs[1][i] = 'A' + i;
    }
    for (int i = 0; i < cs.size(); i++) {
      for (int j = 0; j < strlen(cs[i]); j++) {
        std::cout << cs[i][j] << std::endl;
      }
      std::cout << "..." << std::endl;
    }

    for (int i = 0; i < cs.size(); i++) {
      delete[] (char*)cs[i];
      // free(cs[i]);
    }
  }

  {
    std::cout << " ---5 " << std::endl;
    std::vector<void*> cs(2);
    cs[0] = (void*)new char[10];
    cs[1] = (void*)new char[10];

    // 赋值
    char* p1 = (char*)cs[0];
    char* p2 = (char*)cs[1];
    for (int i = 0; i < 10; i++) {
      p1[i] = 'a' + i;
      p2[i] = 'a' + i + 1;
    }

    for (const auto& c : cs) {
      for (char* i = (char*)c; *i != '\0'; i++) {
        std::cout << *i << std::endl;
      }
      std::cout << " ... " << std::endl;
    }
    for (int i = 0; i < cs.size(); i++) {
      // delete[] (char*)cs[i];
      free(cs[i]);
    }
  }
  return 0;
}
