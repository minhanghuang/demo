#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

int main() {
  std::cout << "Hello, nlohmann json!" << std::endl;
  {
    std::cout << "@@@@@ 字符串转json @@@@@" << std::endl;
    std::string s =
        "{ \"happy\": true, \"pi\": 3.141,  \"name\": \"\",  \"age\": 99 }";
    nlohmann::json js = nlohmann::json::parse(s);
    std::cout << js << std::endl;
    std::cout << "name:" << js["name"].get<std::string>() << std::endl;
    std::cout << "oooo:" << js["oooo"].is_null() << std::endl;
    std::cout << "age:" << js["age"].is_null() << std::endl;
  }

  {
    std::cout << "@@@@@  移除不必要的空格 @@@@@" << std::endl;
    nlohmann::json data;
    for (int i = 0; i < 1000; i++) {
      data[i][0] = i;
      data[i][1] = i + 100;
    }
    // 用于指定缩进的空格数或制表符数。默认值为-1，表示不使用缩进，即生成压缩的JSON字符串。
    // 如果将该参数设置为0或正整数，则输出的JSON字符串将使用该数量的空格或制表符进行缩进。例如，设置indent=4时，JSON字符串将缩进4个空格。
    std::string dump_default = data.dump();
    std::string dump_0 = data.dump(0);

    std::cout << "default:" << dump_default.size() << std::endl;
    std::cout << "0:" << dump_0.size() << std::endl;
  }

  {
    std::cout << "@@@@@ 数据类型转换 @@@@@" << std::endl;
    std::string s =
        "{ \"happy\": true, \"pi\": 3.141,  \"name\": \"\",  \"age\": 99 }";
    nlohmann::json js = nlohmann::json::parse(s);
    std::cout << "json: " << js << std::endl;
    // std::string pi = js["pi"].get<std::string>(); // err
    // std::string pi(js["pi"].dump()); // ok
    std::string pi = js["pi"].dump();  // ok
    std::cout << "string pi: " << pi << std::endl;
  }
  return 0;
}
