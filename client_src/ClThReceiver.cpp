#include "ClThReceiver.h"
#include <iostream>

#include "GameModelClient.h"

ClThReceiver::ClThReceiver(Socket* socket):
        socket(socket), _userClient(nullptr), _gameModel(nullptr){
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
        _userClient->stop();
    }
}

void ClThReceiver::stop(){
    is_running = false;
}

void ClThReceiver::setUserClient(UserClient* user_client){
    _userClient = user_client;
}

void ClThReceiver::processReception(Protocol& protocol){
    switch (protocol.getAction()){
        case Protocol::action::CREATE_GAME:
            _userClient->push(protocol);
            break;
        case Protocol::action::JOIN_GAME:
            _userClient->push(protocol);
            break;
        case Protocol::action::OK:
            _userClient->push(protocol);
            break;
        case Protocol::action::LAUNCH_GAME:
            _userClient->push(protocol);
            break;
        case Protocol::action::BEGIN:
            _userClient->push(protocol);
            break;
        case Protocol::action::ERROR:
            _userClient->push(protocol);
            break;
        case Protocol::action::ADD_PLAYER:
            if (_gameModel == nullptr){
                _userClient->push(protocol);
            } else {
                _gameModel->addPlayer(protocol.getId());
            }
            break;
        case Protocol::action::REMOVE:
            _userClient->removePlayer(protocol.getUserId());
            break;
        case Protocol::action::END:
            _userClient->push(protocol);
            break;
        case Protocol::action::MOVE:
            _gameModel->push(protocol);
            break;
        case Protocol::action::SHOOT:
            _gameModel->push(protocol);
            break;
        case Protocol::action::SHOOTED:
            _gameModel->push(protocol);
            break;
        case Protocol::action::DIE:
            _gameModel->push(protocol);
            break;
        case Protocol::action::RESURRECT:
            _gameModel->push(protocol);
            break;
        default:
            // TODO: la parte que no es crear o unirse a una partida,
            // se lo envia directamente al game model
            break;
    }
}

void ClThReceiver::setGameModel(GameModelClient* gameModel){
    _gameModel = gameModel;
}

GameModelClient* ClThReceiver::getGameModel(){
    return _gameModel;
}

ClThReceiver::~ClThReceiver(){
}
