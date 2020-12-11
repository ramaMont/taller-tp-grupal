#include "ServerHolder.h"
#include <ThAcceptor.h>
#include <iostream>
#include "GamesAdmin.h"

ServerHolder::ServerHolder(int argc, char** argv):
    paramReader(argc, argv){
}

void ServerHolder::run(){
    std::string run;
    GamesAdmin games_admin;
    ThAcceptor th_acceptor(paramReader.getPort(), games_admin);
    th_acceptor.start();
    while (run != "q")
        std::cin >> run;
    th_acceptor.stop();
    th_acceptor.join();
}

ServerHolder::~ServerHolder(){
}
