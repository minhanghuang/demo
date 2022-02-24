#include <csignal>
#include <vector>
#include <memory>
#include <iostream>

void SignalHandlerINT(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;
    exit(signum);
}

void SignalHandlerABRT(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;
    exit(signum);
}

void SignalHandlerSEGV(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;
    exit(signum);
}

class Cla {
public:
    Cla()=default;
    int v = 99;
};

void Ex() {
//    std::vector<int> a{1,2,3};
//    std::cout << a.at(100) << std::endl;

    std::shared_ptr<Cla> b;
    std::cout << b->v << std::endl;
}

int main() {
    std::cout << "Hello, Signal!" << std::endl;
    signal(SIGINT, SignalHandlerINT);
    signal(SIGABRT, SignalHandlerABRT);
    signal(SIGSEGV, SignalHandlerSEGV);
//    raise(SIGINT);
    Ex();
    return 0;
}
