#include "reactor.h"
#include <iostream>

int main() {
    try {
        Reactor reactor(4, 8080); // 4 threads, port 8080
        std::cout << "Starting Server on port 8080..." << std::endl;
        reactor.start();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}