#include <iostream>
#include "ServerHolder.h"

int main(int argc, char** argv){
    try {
        ServerHolder serverHolder(argc, argv);
        serverHolder.run();
    } catch(...) {
        std::cout << "Hubo un error" << std::endl;
    }
    return 0;
}
