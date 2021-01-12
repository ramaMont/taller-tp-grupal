#include "ClientHolder.h"

#include "Posicionable.h"

#include "ClThReceiver.h"
#include <ThSender.h>
#include <UserClient.h>
#include <QApplication>
#include <LoginWindow.h>

#include <iostream>

ClientHolder::ClientHolder(){
    socket = nullptr;
}

void ClientHolder::logginScreen(){
    std::cout << "Ingrese su nick name:\n";
    std::cin >> _player_name;
    std::cout << "El server al que quiere conectarse\n";
    std::cin >> _host_dns;
    std::cout << "El puerto al que quiere conectarse\n";
    std::cin >> _port;
}

void ClientHolder::crearPartida(std::string& id_mapa) {
    int map_id = std::stoi(id_mapa);
    ClThReceiver th_receiver(socket);
    ThSender th_sender(id, socket);
    UserClient user_client(id, th_receiver, th_sender);
    th_receiver.setUserClient(&user_client);

    th_receiver.start();
    th_sender.start();

    user_client.createGame(map_id);
    th_receiver.stop();
    th_receiver.join();
    th_sender.stop();
    th_sender.join();
}

void ClientHolder::unirseAPartida(std::string& id_partida) {
    int game_id = std::stoi(id_partida);
    ClThReceiver th_receiver(socket);
    ThSender th_sender(id, socket);
    UserClient user_client(id, th_receiver, th_sender);
    th_receiver.setUserClient(&user_client);

    th_receiver.start();
    th_sender.start();

    user_client.joinGame(game_id);
    th_receiver.stop();
    th_receiver.join();
    th_sender.stop();
    th_sender.join();
}

void ClientHolder::logged(std::string& nombre, std::string& puerto, std::string& servidor){
    _player_name = nombre;
    _port = puerto;
    _host_dns = servidor;
    Protocol protocol;
    socket = new SocketClient(_host_dns, _port);
    socket->recive(protocol, sizeof(Protocol));
    setId(protocol);
    std::cout << "Id del jugador: " << std::to_string(id);
    //ClThReceiver th_receiver(&socket);
    //ThSender th_sender(id, &socket);
    //UserClient user_client(id, th_receiver, th_sender);
    //th_receiver.setUserClient(&user_client);

    //th_receiver.start();
    //th_sender.start();

    //user_client.run();
    //th_receiver.stop();
    //th_receiver.join();
    //th_sender.stop();
    //th_sender.join();
}

void ClientHolder::run(){
    //logginScreen();
    //Mandar esto a un metodo de ClientHolder que se llame logged().
    //Los threads los lanza como punteros. Y despues en el destructor hacer delete,
    //si fueron lanzados.
    //int id;
    //Protocol protocol;
    //SocketClient socket(_host_dns, _port);
    //socket.recive(protocol, sizeof(Protocol));
    //setId(protocol, id);
    //ClThReceiver th_receiver(&socket);
    //ThSender th_sender(id, &socket);
    //UserClient user_client(id ,th_receiver, th_sender);
    //th_receiver.setUserClient(&user_client);
    //
    //th_receiver.start();
    //th_sender.start();
    // 
    //user_client.run();
    //std::thread t1
    // (
    //     [&]
    //     {
    char *argv[] = {NULL};
    int argc = 1;
    QApplication app(argc, argv);
    // // Instancio el greeter
    LoginWindow loginWindow(*this);
    loginWindow.show();
    // // Arranca el loop de la UI
    app.exec();
    std::cout << "CERRE LA APP" << std::endl;
    //play();
    //     }
    // );
    // t1.join();
     
     std::cout << "Finalizada";

    //th_receiver.stop();
    //th_receiver.join();
    //th_sender.stop();
    //th_sender.join();
}

void ClientHolder::setId(Protocol& protocol){
    if (protocol.getAction() != Protocol::action::SET_ID)
        throw -1;
    id = protocol.getId();
}

ClientHolder::~ClientHolder(){
    delete socket;
}
