#include <iostream>
#include <nlohmann/json.hpp>


int main() {
    std::cout << "Hello, nlohmann json!" << std::endl;
    // 1. 字符串转json
    std::string s = "{ \"happy\": true, \"pi\": 3.141 }";
    nlohmann::json js = nlohmann::json::parse(s);
    std::cout << js << std::endl;
    return 0;
}
