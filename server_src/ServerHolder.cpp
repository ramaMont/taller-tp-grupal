#include "ServerHolder.h"
#include <ThAcceptor.h>
#include <iostream>

ServerHolder::ServerHolder(int argc, char** argv):
    paramReader(argc, argv){
}

void ServerHolder::run(){
    std::string run;
    ThAcceptor th_acceptor(paramReader.getPort());
    th_acceptor.start();
    while (run != "q")
        std::cin >> run;
    th_acceptor.stop();
    th_acceptor.join();
}

ServerHolder::~ServerHolder(){
}
