#include "ThGameModelServer.h"

#include <vector>
#include <map>
#include <utility>

ThGameModelServer::ThGameModelServer(ThUserServer& th_user_server,
        int map_id, int game_id):
    GameModel(map_id, game_id), launched(false){
    addThSender(th_user_server.getSender());
    addPlayer(th_user_server.getId());
    th_user_server.setGameModel(this);
}

void ThGameModelServer::processProtocol(Protocol& protocol){
    switch (protocol.getAction()){
        case Protocol::action::MOVE:
            processMove(protocol);
            echoProtocol(protocol);
            break;
        case Protocol::action::SHOOT:
            // TODO
            break;
        default:
            break;
    }
}

void ThGameModelServer::addThSender(ThSender* th_sender){
    users_sender.insert(std::pair<int, ThSender*>(th_sender->getId(),
        th_sender));
}

void ThGameModelServer::echoProtocol(Protocol protocol){
    std::map<int, ThSender *>::iterator it = users_sender.begin();
    while (it != users_sender.end()){
        ThSender* user_sender = it->second;
        user_sender->push(protocol);
        ++it;
    }
}

void ThGameModelServer::run(){
    launched = true;
    Protocol protocol;
    protocol.setAction(Protocol::action::BEGIN);
    echoProtocol(protocol);
    try{
        while (is_running){
            protocol = operations.pop();
            processProtocol(protocol);
        }
    } catch(...){
        is_running = false;
    }
}

void ThGameModelServer::removePlayer(int user_id){
    auto player = players.at(user_id);
    auto coordenadas = player->get_coordinates();
    delete(player);
    players.erase(user_id);
    users_sender.erase(user_id);
    Protocol protocol(user_id);
    map.sacarPosicionable(coordenadas);
    protocol.setAction(Protocol::action::REMOVE);
    echoProtocol(protocol);
}

void ThGameModelServer::stop(){
    is_running = false;
    operations.stop();
}

bool ThGameModelServer::isDone(){
    if (players.size() == 0)
        return true;
    return !is_running;
}

bool ThGameModelServer::wasLaunched(){
    return launched;
}

ThGameModelServer::~ThGameModelServer(){
    // Todos los jugadores son limpiados en la funcion 
    // removePlayer la cual es llamada cada vez que un jugador
    // se desconecta o se frena la ejecucion de un ThUserServer
}
