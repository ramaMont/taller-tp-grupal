#include "ClientHolder.h"

#include "Posicionable.h"

#include "ClThReceiver.h"
#include <ThSender.h>
#include <UserClient.h>
#include <QApplication>
#include <LoginWindow.h>

#include <ConfigVariable.h>
std::map<int, float> configs;

#include <iostream>
#include <MapLoader.h>

ClientHolder::ClientHolder(): 
    user_id(-1), socket(nullptr), _game_model(nullptr), 
    _cl_th_receiver(nullptr), _th_sender(nullptr), ready_to_play(false),
    _game_id(-1), _map_id_checksum(-1){
}

void ClientHolder::crearPartida(const std::string& map_filename,
            int bots_cty ,int& game_id){
    _map_filename = map_filename;
    MapLoader mapLoader(map_filename);
    int map_id_checksum = mapLoader.getChecksum();
    Protocol protocol_send(bots_cty, map_id_checksum);
    Protocol protocol_response;
    protocol_send.setAction(Protocol::action::CREATE_GAME);
    socket->send(protocol_send, sizeof(protocol_send));
    socket->recive(protocol_response, sizeof(protocol_response));
    processReception(protocol_response);
    game_id = _game_id;
    socket->recive(protocol_response, sizeof(protocol_response));
    processReception(protocol_response);
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
    receiveConfiguration();
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
}

void ClientHolder::run(){
    logginScreen();

    if (!ready_to_play) 
        return;
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
        case Protocol::action::OK:{
            _game_id = protocol.getGameId();
            _map_id_checksum = protocol.getMapId();
            if (_map_filename.size() == 0){
                MapLoader mapLoader(_map_id_checksum);
                _map_filename = mapLoader.getFileName();
            }
            break;
        }
        case Protocol::action::CREATE_GAME:{
            // TODO: agregar en el createGameModel la cantidad de Bots
            // 
            createGameModel(_map_filename, user_id, _game_id);
            std::cout << "Partida creada\nId de Partida: " << 
                _game_id << std::endl;
            _game_model->addPlayer(protocol);
            break;
        }
        case Protocol::action::ADD_PLAYER:{
            if (_game_model == nullptr){
                createGameModel(_map_filename, protocol.getUserId(), 
                    _game_id);
                _game_model->addPlayer(protocol);
            }
            else{
                _game_model->addPlayer(protocol);
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

void ClientHolder::createGameModel(std::string map_filename, int id_user_protocol, int game_id){
    _game_model = new GameModelClient(id_user_protocol, map_filename, game_id, user_id);
}

void ClientHolder::startGame(){
    ready_to_play = true;
    qApp->exit();
}

void ClientHolder::addLoggedUsers(){
    Protocol protocol_response;
    bool ready = false;
    while (!ready){
        socket->recive(protocol_response, sizeof(protocol_response));
        processReception(protocol_response);
        if (protocol_response.getAction() == Protocol::action::END)
            ready = true;
    }
    socket->recive(protocol_response, sizeof(protocol_response));
    processReception(protocol_response);
    _cl_th_receiver = new ClThReceiver(socket, *this, _game_model);
    _cl_th_receiver->start();
    _th_sender = new ThSender(user_id, socket);
    _th_sender->start();
}

void ClientHolder::receiveConfiguration(){
    bool ready = false;
    Protocol protocol_config;
    while (!ready){
        socket->recive(protocol_config, sizeof(protocol_config));
        if (protocol_config.getAction() == Protocol::action::END)
            ready = true;
        else
            configs.insert(std::pair<int, float>((protocol_config.getConfId()),
                protocol_config.getConfiguration()));
    }
}

ClientHolder::~ClientHolder(){
    if (socket != nullptr)
        delete socket;
    if (_game_model != nullptr)
        delete _game_model;
    if (_cl_th_receiver != nullptr){
        _cl_th_receiver->stop();
        _cl_th_receiver->join();
        delete _cl_th_receiver;
    }
    if (_th_sender != nullptr){
        _th_sender->stop();
        _th_sender->join();
        delete _th_sender;
    }
}
