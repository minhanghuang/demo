#include <iostream>
#include <nlohmann/json.hpp>


int main() {
    std::cout << "Hello, nlohmann json!" << std::endl;
    // 1. 字符串转json
    std::string s = "{ \"happy\": true, \"pi\": 3.141,  \"name\": \"\",  \"age\": 99 }";
    nlohmann::json js = nlohmann::json::parse(s);
    std::cout << js << std::endl;
    std::cout << "name:" << js["name"].get<std::string>() << std::endl;
    std::cout << "oooo:" << js["oooo"].is_null() << std::endl;
    std::cout << "age:" << js["age"].is_null() << std::endl;
    return 0;
}
