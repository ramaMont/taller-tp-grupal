#include "ClientHolder.h"

#include "Posicionable.h"

#include <Socket.h>
#include "ClThReceiver.h"
#include <ThSender.h>
#include <UserClient.h>

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
    
    // Mandar esto a un metodo de ClientHolder que se llame logged().
    // Los threads los lanza como punteros. Y despues en el destructor hacer delete,
    // si fueron lanzados.
    // int id;
    // Protocol protocol;
    // SocketClient socket(_host_dns, _port);
    // socket.recive(protocol, sizeof(Protocol));
    // setId(protocol, id);
    // ClThReceiver th_receiver(&socket);
    // ThSender th_sender(id, &socket);
    // UserClient user_client(id ,th_receiver, th_sender);
    // th_receiver.setUserClient(&user_client);

    // th_receiver.start();
    // th_sender.start();
// 
    // user_client.run();

    // QApplication app();
    // // Instancio el greeter
    // LoginWindow loginWindow(this);
    // loginWindow.show();
    // // Arranca el loop de la UI
    // app.exec();

    th_receiver.stop();
    th_receiver.join();
    th_sender.stop();
    th_sender.join();
}

void ClientHolder::setId(Protocol& protocol, int& id){
    if (protocol.getAction() != Protocol::action::SET_ID)
        throw -1;
    id = protocol.getId();
}

ClientHolder::~ClientHolder(){
}
