#include "ClientHolder.h"
#include <iostream>

int main(int argc, char* argv[]) {
    ClientHolder clientHolder;
    try{
        clientHolder.run();
    } catch(const std::string &e){
        std::cerr << e;
    } catch(...){
    }
    return 0;
}
