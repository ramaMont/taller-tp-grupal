#include "ClThReceiver.h"
#include <iostream>

ClThReceiver::ClThReceiver(Socket* socket):
        socket(socket), _th_user(nullptr), _gameModel(nullptr){
}

void ClThReceiver::run(){
    Protocol protocol;
    try{
        while (is_running){
            socket->recive(protocol, sizeof(protocol));
            processReception(protocol);
        }
    } catch(...){
        is_running = false;
        _th_user->stop();
    }
}

void ClThReceiver::stop(){
    is_running = false;
}

void ClThReceiver::setThUser(ThUser* th_user){
    _th_user = th_user;
}

void ClThReceiver::processReception(Protocol& protocol){
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
        case Protocol::action::ERROR:
            _th_user->push(protocol);
            break;
        case Protocol::action::ADD_PLAYER:
            if (_gameModel == nullptr){
                _th_user->push(protocol);
            } else {
                _gameModel->addPlayer(protocol.getId());
            }
            break;
        case Protocol::action::REMOVE:
            _th_user->removePlayer(protocol.getUserId());
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

void ClThReceiver::setGameModel(ClientGameModel* gameModel){
    _gameModel = gameModel;
}

ClientGameModel* ClThReceiver::getGameModel(){
    return _gameModel;
}

ClThReceiver::~ClThReceiver(){
}
