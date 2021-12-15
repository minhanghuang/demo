#include <iostream>

#define Max 999

#define add(x,y) x+y

#define LOG_METHOD(NAME,LEVEL) \
    static int NAME(const char* fmt, ...) \
    { \
        return 1; \
    }

int main() {
    std::cout << "Hello, define!" << std::endl;
    std::cout << Max << std::endl;
    std::cout << add(1,4) << std::endl;
    return 0;
}
