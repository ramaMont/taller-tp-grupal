#include <iostream>
#include "ServerHolder.h"
#include <ctime>
#include <exception>


int main(int argc, char** argv){
    srand(time(0));
    try {
        ServerHolder serverHolder(argc, argv);
        serverHolder.run();
    } catch(std::exception& e) {
        std::cout << e.what();
    }
    return 0;
}
