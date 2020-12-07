#include "ClientHolder.h"

int main(int argc, char* argv[]) {
    ClientHolder clientHolder;
    try{
        clientHolder.run();
    } catch (...){
    }
    return 0;
}

