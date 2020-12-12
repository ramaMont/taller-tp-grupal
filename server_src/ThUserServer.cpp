#include "ThUserServer.h"
#include <Protocol.h>
#include <iostream>

ThUserServer::ThUserServer(int user_id, Socket&& socket_peer,
        GamesAdmin& games_admin):
    ThUser(user_id),
    socket_peer(std::move(socket_peer)),
    th_receiver(nullptr),
    th_sender(nullptr),
    games_admin(games_admin),
    game_id(-1){
}

void ThUserServer::sendConfiguration(){
    // TODO: Envio de configuracion al peer.
}

void ThUserServer::respondSuccess(){
    Protocol protocol(game_id);
    protocol.setAction(Protocol::action::OK);
    th_sender->push(protocol);
}

void ThUserServer::initCommunication(){
    Protocol protocol(user_id);
    protocol.setAction(Protocol::action::SET_ID);
    socket_peer.send(protocol, sizeof(Protocol));
    sendConfiguration();
    th_receiver = new ThReceiver(&socket_peer);
    th_receiver->setThUser(this);
    th_sender = new ThSender(user_id, &socket_peer);
    th_receiver->start();
    th_sender->start();
}

void ThUserServer::processReception(Protocol& protocol){
    switch (protocol.getAction()){
        case Protocol::action::CREATE_GAME:{
            int map_id = protocol.getId();
            games_admin.createGame(*this, map_id);
            respondSuccess();
            break;
        }
        case Protocol::action::JOIN_GAME:{
            int game_id = protocol.getId();
            games_admin.joinGame(*this, game_id);
            break;
        }
        case Protocol::action::LAUNCH_GAME:{
            int game_id = protocol.getId();
            games_admin.launchGame(game_id);
            respondSuccess();
            break;
        }
        default:
            std::cout << "Nunca deberia entrar acá\n";
            // TODO: algo salio muy mal.
            break;
    }
}

void ThUserServer::run(){
    initCommunication();
    while (is_running){
        Protocol protocol = operations.pop();
        processReception(protocol);
    }
}

ThSender* ThUserServer::getSender(){
    return th_sender;
}

void ThUserServer::setGameModel(ThGameModelServer* th_game_model){
    th_receiver->setGameModel(th_game_model);
}

void ThUserServer::setGameId(int game_id){
    this->game_id = game_id;
}

void ThUserServer::transmit(std::vector<int>& ids_vector){
    for (auto it = ids_vector.begin(); it != ids_vector.end(); ++it){
        Protocol protocol(*it);
        protocol.setAction(Protocol::action::ADD_PLAYER);
        th_sender->push(protocol);
    }
    Protocol protocol;
    protocol.setAction(Protocol::action::END);
    th_sender->push(protocol);
}

ThUserServer::~ThUserServer(){
    socket_peer.shutdown();
    socket_peer.close();
    if (th_receiver != nullptr){
        th_receiver->stop();
        th_receiver->join();
        delete(th_receiver);
    }
    if (th_sender != nullptr){
        th_sender->stop();
        th_sender->join();
        delete(th_sender);
    }
}
