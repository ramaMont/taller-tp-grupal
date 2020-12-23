#include "ClientHolder.h"
#include <Socket.h>
#include <ThReceiver.h>
#include <ThSender.h>
#include <ThUserClient.h>

#include <iostream>

ClientHolder::ClientHolder(){
}

void ClientHolder::logginScreen(){
    std::cout << "Ingrese su nick name:\n";
    std::cin >> _player_name;
    std::cout << "El server al que quiere conectarse\n";
    std::cin >> _host_dns;
    std::cout << "El puerto al que quiere conectarse\n";
    std::cin >> _port;
}

void ClientHolder::run(){
    logginScreen();
    int id;
    Protocol protocol;
    SocketClient socket(_host_dns, _port);
    socket.recive(protocol, sizeof(Protocol));
    setId(protocol, id);
    ThReceiver th_receiver(&socket);
    ThSender th_sender(id, &socket);
    ThUserClient th_user_client(id ,th_receiver, th_sender);
    th_receiver.setThUser(&th_user_client);

    th_user_client.start();
    th_receiver.start();
    th_sender.start();
    th_receiver.join();
    th_sender.join();
    th_user_client.join();
}

void ClientHolder::setId(Protocol& protocol, int& id){
    if (protocol.getAction() != Protocol::action::SET_ID)
        throw -1;
    id = protocol.getId();
}

ClientHolder::~ClientHolder(){
}
