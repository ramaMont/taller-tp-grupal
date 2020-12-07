#include "ThSender.h"
#include <iostream>

ThSender::ThSender(int id_user, Socket* socket):
        id_user(id_user), socket(socket){
}
void ThSender::run(){
    Protocol protocol(87, Protocol::direction::LEFT);
    std::cout << "Tamaño del protocolo: " << sizeof(Protocol) << std::endl;
    socket->send(protocol, sizeof(Protocol));
    std::cout << "Mensaje enviado\n";
}
void ThSender::push(Protocol protocol){
    operations.push(protocol);
}

int ThSender::getId(){
    return id_user;
}

void ThSender::stop(){
}

ThSender::~ThSender(){
}
