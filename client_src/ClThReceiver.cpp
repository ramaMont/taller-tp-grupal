#include "ClThReceiver.h"
#include <iostream>

#include "GameModelClient.h"

ClThReceiver::ClThReceiver(Socket* socket, ClientHolder& client_holder):
        socket(socket), _client_holder(client_holder), _gameModel(nullptr){
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
    }
}

void ClThReceiver::stop(){
    is_running = false;
}

void ClThReceiver::processReception(Protocol& protocol){
    switch (protocol.getAction()){
        case Protocol::action::BEGIN:
            _client_holder.startGame();
            break;
        case Protocol::action::ADD_PLAYER:
            _gameModel->addPlayer(protocol.getId());
            break;
        case Protocol::action::REMOVE:
            _gameModel->removePlayer(protocol.getUserId());
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
