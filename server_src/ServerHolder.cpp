#include "ServerHolder.h"
#include <Socket.h>
#include <ThReceiver.h>
#include <Protocol.h>
#include <iostream>

ServerHolder::ServerHolder(int argc, char** argv):
    paramReader(argc, argv){
}

void ServerHolder::run(){
    std::string run = "a";
    int id = 1;
    Protocol protocol(id);
    protocol.setAction(Protocol::action::SET_ID);
    SocketServer socket_accept("7777");
    Socket socket_receptor = socket_accept.acceptClient();
    socket_receptor.send(protocol, sizeof(Protocol));
    socket_receptor.recive(protocol, sizeof(Protocol));
    if (protocol.getAction() == Protocol::action::CREATE_GAME){
        Protocol new_protocol;
        new_protocol.setAction(Protocol::action::OK);
        socket_receptor.send(new_protocol, sizeof(Protocol));
    }
    std::cout << "todo hecho\n";
    while (run != "q")
        std::cin >> run;
    // ThReceiver th_receiver(&socket_receptor);
    // th_receiver.start();
    // th_receiver.join();

}

ServerHolder::~ServerHolder(){
}
