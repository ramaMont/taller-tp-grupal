#include "ServerHolder.h"
#include <Socket.h>
#include <ThReceiver.h>
#include <Protocol.h>

ServerHolder::ServerHolder(int argc, char** argv):
    paramReader(argc, argv){
}

void ServerHolder::run(){
    int id = 1;
    Protocol protocol(id);
    protocol.setAction(Protocol::action::SET_ID);
    SocketServer socket_accept("7777");
    Socket socket_receptor = socket_accept.acceptClient();
    socket_receptor.send(protocol, sizeof(Protocol));
    ThReceiver th_receiver(&socket_receptor);
    th_receiver.start();


    th_receiver.join();

}

ServerHolder::~ServerHolder(){
}
