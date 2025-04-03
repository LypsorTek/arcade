#include "Core.hpp"
#include <iostream>

int main(int argc, char** argv) {

    int i = 0;
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <graphics_library.so>" << std::endl;
        return 84;
    }
    
    try {
        Core core(argv[1]);
        core.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
    i = 1;
    return 0;
}