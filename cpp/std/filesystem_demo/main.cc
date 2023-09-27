#include <filesystem>
#include <iostream>

int main(int argc, char* argv[]) {
  std::cout << "Hello, C++17 filesystem" << std::endl;
  {
    std::cout << "@@@@@@@@@@@    路径拼接   @@@@@@@@@@@" << std::endl;
    std::string a = "/var/hmh";
    std::string b = "version.txt";
    std::filesystem::path path =
        std::filesystem::path(a) / std::filesystem::path(b);
    std::cout << "path: " << path.string() << std::endl;
  }
  return 0;
}
