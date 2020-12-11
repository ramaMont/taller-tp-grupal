#include "ThGameModelServer.h"

ThGameModelServer::ThGameModelServer(ThUserServer& th_user_server, int map_id, int game_id):
        GameModel(map_id, game_id){
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

            break;
        default:
            break;
    }
}

void ThGameModelServer::addThSender(ThSender* th_sender){
    users_sender.insert(std::pair<int, ThSender*>(th_sender->getId(), th_sender));
}

void ThGameModelServer::echoProtocol(Protocol protocol){
    std::map<int, ThSender *>::iterator it = users_sender.begin();
    while (it != users_sender.end()){
        ThSender* user_sender = it->second;
        user_sender->push(protocol);
        it++;
    }
}

void ThGameModelServer::run(){
    Protocol protocol;
    protocol.setAction(Protocol::action::BEGIN);
    echoProtocol(protocol);
    while (is_running){
        Protocol protocol = operations.pop();
        processProtocol(protocol);
    }
}

void ThGameModelServer::stop(){
    is_running = false;
}

ThGameModelServer::~ThGameModelServer(){
}
