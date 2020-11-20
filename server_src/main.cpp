#include <iostream>
#include "ParamReaderServer.h"

int main(int argc, char** argv){
    try {
        ParamReaderServer paramReader(argc, argv);
    } catch(...) {
        std::cout << "Hubo un error" << std::endl;
    }
    return 0;
}
