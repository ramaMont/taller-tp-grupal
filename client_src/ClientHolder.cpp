#include "ClientHolder.h"

#include <Posicionable.h>
#include <ThSender.h>
#include <ConfigVariable.h>
#include <MapLoader.h>

#include "ThReceiverClient.h"
#include "UserClient.h"

#include <QApplication>
#include "LoginWindow.h"

#include <iostream>
#include <string>
#include <map>
#include <utility>

std::map<int, float> configs;

ClientHolder::ClientHolder(): 
    user_id(-1), socket(nullptr), _game_model(nullptr), 
    _cl_th_receiver(nullptr), _th_sender(nullptr), ready_to_play(false),
    _game_id(-1), _map_id_checksum(-1), _user_client(nullptr), _winner_id(-1),
    game_done(false), player_alive(true), _have_winner(false){
}

void ClientHolder::setGameConfig(std::string& resolution, bool _fullscreen){
    if (resolution == "320:200"){
        this->resolution_width = 320;
        this->resolution_height = 200;
    } else {
        this->resolution_width = 640;
        this->resolution_height = 400;
    }
    this->fullscreen = _fullscreen;
}

void ClientHolder::crearPartida(const std::string& map_filename,
            int bots_cty ,int& game_id, std::string& resolution,
            bool fullscreen){
    setGameConfig(resolution,fullscreen);
    _map_filename = map_filename;
    MapLoader mapLoader(map_filename);
    int map_id_checksum = mapLoader.getChecksum();
    Protocol protocol_send(bots_cty, map_id_checksum);
    Protocol protocol_response;
    protocol_send.setAction(Protocol::action::CREATE_GAME);
    socket->send(protocol_send);
    socket->recive(protocol_response);
    processReception(protocol_response);
    game_id = _game_id;
    socket->recive(protocol_response);
    processReception(protocol_response);
    _cl_th_receiver = new ThReceiverClient(socket, *this, _game_model);
    _cl_th_receiver->start();
}

void ClientHolder::unirseAPartida(const std::string& id_partida,
                                  std::string& resolution,
                                  bool fullscreen) {
    setGameConfig(resolution,fullscreen);
    int game_id = std::stoi(id_partida);
    Protocol protocol_send(game_id);
    protocol_send.setAction(Protocol::action::JOIN_GAME);
    socket->send(protocol_send);
    addLoggedUsers();
}

void ClientHolder::logged(const std::string& puerto, 
        const std::string& servidor, int& user_id){
    _port = puerto;
    _host_dns = servidor;
    Protocol protocol;
    socket = new SocketClient(_host_dns, _port);
    socket->recive(protocol);
    setId(protocol);
    user_id = this->user_id;
    std::cout << "Id del jugador: " << std::to_string(this->user_id);
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
    //Tiempo de espera hasta que el servidor procese el ingreso del cliente
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    if (!ready_to_play) 
        return;
    // Comienzo el juego luego del setup inicial   
    _user_client = new UserClient(*_th_sender, *_game_model,_winner_id,\
        game_done, _ordered_players_kills, _ordered_players_points,\
        _ordered_players_bullets, player_alive, _have_winner);
    _user_client->play();   
    std::cout << "Finalizada\n";
}

void ClientHolder::setId(Protocol& protocol){
    if (protocol.getAction() != Protocol::action::SET_ID)
        throw -1;
    this->user_id = protocol.getId();
}

void ClientHolder::launchGame() {
    Protocol protocol(_game_model->getId());
    protocol.setAction(Protocol::action::LAUNCH_GAME);
    socket->send(protocol);
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
            } else {
                _game_model->addPlayer(protocol);
            }
            break;
        }
        case Protocol::action::END:
            break;
        case Protocol::action::ERROR:
            // algo salio mal.
            throw -1;
            break;
        default:
            std::cout << "Nunca deberia entrar acá\n";
            // algo salio muy mal.
            break;
    }
}

void ClientHolder::createGameModel(std::string map_filename,\
        int id_user_protocol, int game_id){
    _game_model = new GameModelClient(id_user_protocol, map_filename,\
        game_id, user_id, _winner_id, game_done, _ordered_players_kills,\
        _ordered_players_points, _ordered_players_bullets,\
        resolution_width, resolution_height, fullscreen, player_alive,\
        _have_winner);
}

void ClientHolder::startGame(){
    ready_to_play = true;
    qApp->exit();
}

void ClientHolder::addLoggedUsers(){
    Protocol protocol_response;
    bool ready = false;
    while (!ready){
        socket->recive(protocol_response);
        processReception(protocol_response);
        if (protocol_response.getAction() == Protocol::action::END)
            ready = true;
    }
    socket->recive(protocol_response);
    processReception(protocol_response);
    _cl_th_receiver = new ThReceiverClient(socket, *this, _game_model);
    _cl_th_receiver->start();
    _th_sender = new ThSender(user_id, socket);
    _th_sender->start();
}

void ClientHolder::receiveConfiguration(){
    bool ready = false;
    Protocol protocol_config;
    while (!ready){
        socket->recive(protocol_config);
        if (protocol_config.getAction() == Protocol::action::END)
            ready = true;
        else
            configs.insert(std::pair<int, float>((protocol_config.getConfId()),
                protocol_config.getConfiguration()));
    }
}

void ClientHolder::connectionLost(){
    if (_user_client != nullptr)
        _user_client->stop();
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
    if (_user_client != nullptr){
        _user_client->stop();
        delete _user_client;
    }
}
