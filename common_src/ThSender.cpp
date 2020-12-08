#include "ThSender.h"
#include <iostream>

ThSender::ThSender(int id_user, Socket* socket):
        id_user(id_user), socket(socket){
}
void ThSender::run(){
    while (is_running){

        Protocol protocol = operations.pop();
        socket->send(protocol, sizeof(Protocol));

    }
}
void ThSender::push(Protocol protocol){
    operations.push(protocol);
}

int ThSender::getId(){
    return id_user;
}

void ThSender::stop(){
    is_running = false;
}

ThSender::~ThSender(){
}
