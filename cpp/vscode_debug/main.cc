#include<iostream>
#include<vector>

int main(int argc, char* argv[]){

    std::cout << "hello vscode debug" << std::endl;    
    for(int i = 0 ; i < argc ; i++){
        std::cout << argv[i] << std::endl;
        std::cout << argv[i] << std::endl;
        std::cout << argv[i] << std::endl;
    }
    
    std::vector<int> a;
    a.push_back(1);
    a.push_back(1);
    a.push_back(1);
    a.push_back(1);
    a.push_back(9);

    return 0;
}
