// Example program
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

int main() {
  // std::string uri = "http://127.0.0.1";
  // std::string uri = "http://127.0.0.1/";
  // std::string uri = "http://127.0.0.1/hello";
  // std::string uri = "http://127.0.0.1:9999/hello";
  std::string uri = "https://www.example.com:8080/path/to/resource";
  // 正则表达式模式，用于匹配 URI 中的协议、域名、端口号和路径
  std::string pattern = R"((https?)://([^:/]+)(?::(\d+))?(/.*)?)";

  // 输入的 URI

  // 创建正则表达式对象
  std::regex uriRegex(pattern);

  // 使用正则表达式匹配 URI
  std::smatch match;
  if (std::regex_match(uri, match, uriRegex)) {
    // match[1] 匹配协议
    // match[2] 匹配域名
    // match[3] 匹配端口号（如果有的话）
    // match[4] 匹配路径
    std::string protocol = match[1];
    std::string domain = match[2];
    std::string port = match[3];
    std::string path = match[4];
    std::cout << "Protocol: " << protocol << std::endl;
    std::cout << "Domain: " << domain << std::endl;
    if (!port.empty()) {
      std::cout << "Port: " << port << std::endl;
    } else {
      std::cout << "Port: Not specified" << std::endl;
    }
    std::cout << "Path: " << path << std::endl;
  } else {
    std::cout << "Invalid URI" << std::endl;
  }
  return 0;
}
