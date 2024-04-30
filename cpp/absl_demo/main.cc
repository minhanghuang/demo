#include <cstdlib>
#include <iostream>

#include <absl/strings/str_cat.h>
#include <absl/strings/string_view.h>

int main(int argc, char* argv[]) {
  std::cout << "Hello absl." << std::endl;
  {
    std::cout << "## absl::string_view ##" << std::endl;
    // https://zhuanlan.zhihu.com/p/40055705
    std::string str = "Hello, String";
    {
      std::cout << "  ## 初始化 ##" << std::endl;
      absl::string_view view(
          str);  // view只是str的镜像,仅仅包含一个指针和一个长度
      std::cout << "view: " << view << std::endl;
      std::cout << "view[0,5]: " << view.substr(0, 5) << std::endl;
    }
    {
      std::cout << "  ## 遍历 ##" << std::endl;
      absl::string_view view(str);
      for (auto it = view.begin(); it != view.end(); it++) {
        std::cout << "  s: " << *it << std::endl;
      }
    }
    {
      std::cout << "  ## 查找 ##" << std::endl;
      absl::string_view view(str);
      absl::string_view view2("Hello");
      auto pos = view.find(view2);  // 0
      pos = view.find("hello");     // absl::string_view::npos
      pos = view.find(view2, 3);  // 从第三位开始查找, absl::string_view::npos
    }
    {
      std::cout << "  ## 拼接 ##" << std::endl;
      absl::string_view view("hello");
      std::string str = " , ";
      const char* cstr = "string ";
      int i = 888;
      double f = 3.14;
      std::string res = absl::StrCat(view, str, cstr, i, f);
      std::cout << res << std::endl;
    }
  }
  return EXIT_SUCCESS;
}
