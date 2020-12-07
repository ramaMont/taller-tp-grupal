#include "ServerHolder.h"
#include <Socket.h>
#include <ThReceiver.h>

ServerHolder::ServerHolder(int argc, char** argv):
    paramReader(argc, argv){
}

void ServerHolder::run(){

    SocketServer socket_accept("7777");
    Socket socket_receptor = socket_accept.acceptClient();
    ThReceiver th_receiver(&socket_receptor);
    th_receiver.start();


    th_receiver.join();

}

ServerHolder::~ServerHolder(){
}
