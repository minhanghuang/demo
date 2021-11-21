#include <iostream>
#include "src/lru_cache.h"


struct Node {
    int id=0;
};



int main() {
    std::cout << "Hello, LRU!" << std::endl;
    cache::lru_cache<std::string, Node> cache(3);
    std::cout << "init cache count: " << cache.size() << std::endl;
    Node n1{1};
    Node n2{2};
    Node n3{3};
    Node n4{4};
    cache.put("1",n1);
    cache.put("2",n2);
    cache.put("3",n3);
    std::cout << "1 cache count: " << cache.size() << std::endl;
    cache.get("1");
    cache.get("3");
    cache.put("4",n4);
    std::cout << "2 cache count: " << cache.size() << std::endl;
    std::cout << "3 cache exists: " << cache.exists("1") << std::endl;
    std::cout << "3 cache exists: " << cache.exists("2") << std::endl;

    return 0;
}
