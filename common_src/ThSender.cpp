#include "ThSender.h"
#include <iostream>

ThSender::ThSender(int id_user, Socket* socket):
        operations(), id_user(id_user), socket(socket){
}
void ThSender::run(){
    try{
        while (is_running){
            Protocol protocol = operations.pop();
            socket->send(protocol);
        }
    } catch(...){
        is_running = false;
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
    operations.stop();
}

ThSender::~ThSender(){
}
