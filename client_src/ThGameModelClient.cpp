#include "ThGameModelClient.h"

ThGameModelClient::ThGameModelClient(int user_id, int map_id,
        int game_id) : Thread(),ClientGameModel(map_id, game_id), is_running(true){
    addPlayer(user_id);
}

void ThGameModelClient::processProtocol(Protocol& protocol){
    switch (protocol.getAction()){
        case Protocol::action::MOVE:
            processMove(protocol);
            break;
        case Protocol::action::SHOOT:

            break;
        case Protocol::action::REMOVE:
            removePlayer(protocol.getUserId());
            break;
        default:
            break;
    }
}

void ThGameModelClient::run(){
    while (is_running){
        Protocol protocol = operations.pop();
        processProtocol(protocol);
    }
}

void ThGameModelClient::removePlayer(int user_id){
    auto coordenadas = movables.at(user_id)->get_position();
    movables.erase(user_id);
    map.sacarPosicionable(coordenadas);
}

void ThGameModelClient::stop(){
    is_running = false;
}

ThGameModelClient::~ThGameModelClient(){
}