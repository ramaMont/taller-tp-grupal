#include <iostream>
#include "ServerHolder.h"
#include <ctime>


int main(int argc, char** argv){
    srand(time(0));
    try {
        ServerHolder serverHolder(argc, argv);
        serverHolder.run();
    } catch(...) {
        std::cout << "Hubo un error" << std::endl;
    }
    return 0;
}
