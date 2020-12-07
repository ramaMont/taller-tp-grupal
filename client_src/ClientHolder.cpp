#include "ClientHolder.h"
#include <Socket.h>
#include <ThReceiver.h>
#include <ThSender.h>

ClientHolder::ClientHolder(){
}

void ClientHolder::run(){
    int id = 1;
    SocketClient socket("localhost", "7777");
//    ThReceiver th_receiver(&socket);
    ThSender th_sender(id, &socket);
//    th_receiver.start();
    th_sender.start();

//    th_receiver.join();
    th_sender.join();

}

ClientHolder::~ClientHolder(){
}