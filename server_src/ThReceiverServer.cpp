#include "ThReceiverServer.h"

#include <iostream>

ThReceiverServer::ThReceiverServer(Socket* socket):
        ThReceiver(socket), _th_user_server(nullptr), _gameModel(nullptr){
}

void ThReceiverServer::run(){
    Protocol protocol;
    try{
        while (is_running){
            socket->recive(protocol);
            processReception(protocol);
        }
    } catch(...){
        is_running = false;
        _th_user_server->stop();
    }
}

void ThReceiverServer::stop(){
    is_running = false;
}

void ThReceiverServer::setThUser(ThUserServer* th_user_server){
    _th_user_server = th_user_server;
}

void ThReceiverServer::setGameModel(ThGameModelServer* gameModel){
    _gameModel = gameModel;
}

void ThReceiverServer::processReception(Protocol& protocol){
    switch (protocol.getAction()){
        case Protocol::action::CREATE_GAME:
            _th_user_server->push(protocol);
            break;
        case Protocol::action::JOIN_GAME:
            _th_user_server->push(protocol);
            break;
        case Protocol::action::OK:
            _th_user_server->push(protocol);
            break;
        case Protocol::action::LAUNCH_GAME:
            _th_user_server->push(protocol);
            break;
        case Protocol::action::BEGIN:
            _th_user_server->push(protocol);
            break;
        case Protocol::action::ERROR:
            _th_user_server->push(protocol);
            break;
        case Protocol::action::ADD_PLAYER:
            if (_gameModel == nullptr){
                _th_user_server->push(protocol);
            } else {
                _gameModel->addPlayer(protocol.getId());
            }
            break;
        case Protocol::action::END:
            _th_user_server->push(protocol);
            break;
        // En el caso de: MOVE, SHOOT, SHOOTED, DIE, RESURRECT, OPEN, OPENING,
        // CLOSE y SWITCH_GUN:
        default:
            _gameModel->push(protocol);
            break;
    }
}

GameModel* ThReceiverServer::getGameModel(){
    return _gameModel;
}

ThReceiverServer::~ThReceiverServer(){
}
