#include "ClientHolder.h"

#include "Posicionable.h"

#include "ClThReceiver.h"
#include <ThSender.h>
#include <UserClient.h>
#include <QApplication>
#include <LoginWindow.h>

#include <iostream>

ClientHolder::ClientHolder(): 
    user_id(-1), socket(nullptr), _game_model(nullptr), 
    _cl_th_receiver(nullptr), _th_sender(nullptr){
}

void ClientHolder::crearPartida(const std::string& id_mapa,
            int& game_id){
    int map_id = std::stoi(id_mapa);
    Protocol protocol_send(map_id);
    Protocol protocol_response;
    protocol_send.setAction(Protocol::action::CREATE_GAME);
    socket->send(protocol_send, sizeof(protocol_send));
    socket->recive(protocol_response, sizeof(protocol_response));
    processReception(protocol_response);
    socket->recive(protocol_response, sizeof(protocol_response));
    processReception(protocol_response);
    game_id = protocol_response.getGameId();
    _cl_th_receiver = new ClThReceiver(socket, *this, _game_model);
    _cl_th_receiver->start();
}

void ClientHolder::unirseAPartida(std::string& id_partida) {
    int game_id = std::stoi(id_partida);
    Protocol protocol_send(game_id);

    protocol_send.setAction(Protocol::action::JOIN_GAME);
    socket->send(protocol_send, sizeof(protocol_send));
    addLoggedUsers();

}

void ClientHolder::logged(std::string& nombre, std::string& puerto, std::string& servidor){
    _player_name = nombre;
    _port = puerto;
    _host_dns = servidor;
    Protocol protocol;
    socket = new SocketClient(_host_dns, _port);
    socket->recive(protocol, sizeof(Protocol));
    setId(protocol);
    std::cout << "Id del jugador: " << std::to_string(user_id);
}

void ClientHolder::logginScreen(){
    char *argv[] = {NULL};
    int argc = 1;
    QApplication app(argc, argv);
    // // Instancio el greeter
    LoginWindow loginWindow(*this);
    loginWindow.show();
    // // Arranca el loop de la UI
    app.exec();
    std::cout << "CERRE LA APP" << std::endl;
//    startGame();
}

void ClientHolder::run(){
    logginScreen();
    // Comienzo el juego luego del setup inicial   
    UserClient user_client(*_th_sender, *_game_model);
    user_client.play();   
    std::cout << "Finalizada\n";
}

void ClientHolder::setId(Protocol& protocol){
    if (protocol.getAction() != Protocol::action::SET_ID)
        throw -1;
    user_id = protocol.getId();
}

void ClientHolder::launchGame() {
    Protocol protocol(_game_model->getId());
    protocol.setAction(Protocol::action::LAUNCH_GAME);
    socket->send(protocol, sizeof(protocol));
    _th_sender = new ThSender(user_id, socket);
    _th_sender->start();
}

void ClientHolder::processReception(Protocol& protocol){
    switch (protocol.getAction()){
        case Protocol::action::OK:
            break;
        case Protocol::action::CREATE_GAME:
            createGameModel(protocol.getMapId(), user_id, protocol.getGameId());
            std::cout << "Partida creada\nId de Partida: " << 
                protocol.getGameId() << std::endl;
            break;
        case Protocol::action::ADD_PLAYER:{
            if (_game_model == nullptr){
                protocol.getUserId();
                createGameModel(protocol.getMapId(), protocol.getUserId(), 
                    protocol.getGameId());
            }
            else{
                _game_model->addPlayer(protocol.getUserId());
            }
            break;
        }
        case Protocol::action::END:
            break;
        case Protocol::action::ERROR:
            // TODO: algo salio mal.
            throw -1;
            break;
        default:
            std::cout << "Nunca deberia entrar acá\n";
            // TODO: algo salio muy mal.
            break;
    }
}

void ClientHolder::createGameModel(int map_id, int id_user_protocol, int game_id){
    _game_model = new GameModelClient(id_user_protocol, map_id, game_id, user_id);
}

void ClientHolder::startGame(){
    // TODO:Cerrar ventana de QT
    qApp->exit();
}

void ClientHolder::addLoggedUsers(){
    Protocol protocol_response;
    bool ready = false;
    while (!ready){
        socket->recive(protocol_response, sizeof(protocol_response));
        
    }

}

ClientHolder::~ClientHolder(){
    if (socket != nullptr)
        delete socket;
    if (_game_model != nullptr)
        delete _game_model;
    if (_cl_th_receiver != nullptr)
        delete _cl_th_receiver;
    if (_th_sender != nullptr)
        delete _th_sender;
}
