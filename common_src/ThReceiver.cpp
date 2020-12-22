#include "ThReceiver.h"
#include <iostream>

ThReceiver::ThReceiver(Socket* socket):
        socket(socket), _th_user(nullptr), _gameModel(nullptr){
}

void ThReceiver::run(){
    Protocol protocol;
    while (is_running){
        socket->recive(protocol, sizeof(protocol));
        processReception(protocol);
    }
}

void ThReceiver::stop(){
    is_running = false;
}

void ThReceiver::setThUser(ThUser* th_user){
    _th_user = th_user;
}

void ThReceiver::processReception(Protocol& protocol){
    switch (protocol.getAction()){
        case Protocol::action::CREATE_GAME:
            _th_user->push(protocol);
            break;
        case Protocol::action::JOIN_GAME:
            _th_user->push(protocol);
            break;
        case Protocol::action::OK:
            _th_user->push(protocol);
            break;
        case Protocol::action::LAUNCH_GAME:
            _th_user->push(protocol);
            break;
        case Protocol::action::BEGIN:
            _th_user->push(protocol);
            break;
        case Protocol::action::ADD_PLAYER:
            if (_gameModel == nullptr){
                _th_user->push(protocol);
            } else {
                _gameModel->addPlayer(protocol.getId());
            }
            break;
        case Protocol::action::END:
            _th_user->push(protocol);
            break;
        case Protocol::action::MOVE:
            _gameModel->push(protocol);
            break;
        default:
            // TODO: la parte que no es crear o unirse a una partida,
            // se lo envia directamente al game model
            break;
    }
}

void ThReceiver::setGameModel(GameModel* gameModel){
    _gameModel = gameModel;
}

GameModel* ThReceiver::getGameModel(){
    return _gameModel;
}

ThReceiver::~ThReceiver(){
    if (_gameModel != nullptr)
        delete(_gameModel);
}
