#include "ThReceiver.h"
#include <iostream>

ThReceiver::ThReceiver(Socket* socket):
        socket(socket){
}

void ThReceiver::run(){
    Protocol protocol;
    socket->recive(protocol, sizeof(protocol));
    std::cout << "------------ Accion --------\n";
    std::cout << protocol.getAction() << std::endl;
    if (protocol.getAction() == Protocol::action::MOVE)
        std::cout << "accion de moverse\n";
    std::cout << "---------- Direccion --------\n";
    std::cout << protocol.getDirection() << std::endl;
    if (protocol.getDirection() == Protocol::direction::LEFT)
        std::cout << "movimiento hacia la izquierda\n";
    std::cout << "---------- ID --------\n";
    std::cout << protocol.getId() << std::endl;
}

void ThReceiver::push(Protocol protocol){
    operations.push(protocol);
}

void ThReceiver::stop(){
}

ThReceiver::~ThReceiver(){
}
