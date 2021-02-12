#include "ThReceiverClient.h"
#include <iostream>

#include "GameModelClient.h"
#include <SocketException.hpp>

ThReceiverClient::ThReceiverClient(Socket* socket, ClientHolder& client_holder,
        GameModelClient* game_model_client):
        ThReceiver(socket), _client_holder(client_holder), _gameModel(game_model_client){
}

void ThReceiverClient::run(){
    Protocol protocol;
    try{
        while (is_running){
            socket->recive(protocol);
            processReception(protocol);
        }
    } catch(SocketException& exc){
        std::cout << exc.what();
        is_running = false;
        _client_holder.connectionLost();
    } catch(...){
        is_running = false;
        _client_holder.connectionLost();
    }
}

void ThReceiverClient::stop(){
    is_running = false;
}

void ThReceiverClient::processReception(Protocol& protocol){
    switch (protocol.getAction()){
        case Protocol::action::BEGIN:
            _client_holder.startGame();
            break;
        case Protocol::action::ADD_PLAYER:
            _gameModel->addPlayer(protocol);
            break;
        case Protocol::action::REMOVE:
            _gameModel->removeEnemy(protocol.getUserId());
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
        case Protocol::action::OPEN:
            _gameModel->push(protocol);
            break;
        case Protocol::action::OPENING:
            _gameModel->push(protocol);
            break;
        case Protocol::action::CLOSE:
            _gameModel->push(protocol);
            break;
        case Protocol::action::ADDPOINTS:
            _gameModel->push(protocol);
            break;
        case Protocol::action::UPDATE_HEALTH:
            _gameModel->push(protocol);
            break;
        case Protocol::action::UPDATE_BULLETS:
            _gameModel->push(protocol);
            break;
        case Protocol::action::PICKUP:
            _gameModel->push(protocol);
            break;
        case Protocol::action::THROW:
            _gameModel->push(protocol);
            break;
        case Protocol::action::SWITCH_GUN:
            _gameModel->push(protocol);
            break;
        case Protocol::action::OPEN_PASSAGE:
            _gameModel->push(protocol);
            break;
        case Protocol::action::ROCKET:
            _gameModel->push(protocol);
            break;
        case Protocol::action::MOVE_ROCKET:
            _gameModel->push(protocol);
            break;
        case Protocol::action::EXPLOSION:
            _gameModel->push(protocol);
            break;
        case Protocol::action::KEY:
            _gameModel->push(protocol);
            break;
        case Protocol::action::END_GAME_BULLETS:
            _gameModel->push(protocol);
            break;
        case Protocol::action::END_GAME_KILLS:
            _gameModel->push(protocol);
            break;
        case Protocol::action::END_GAME_POINTS:
            _gameModel->push(protocol);
            break;
        case Protocol::action::WINNER:
            _gameModel->push(protocol);
            break;
        case Protocol::action::ENDGAME:
            _gameModel->push(protocol);
            break;
        default:
            break;
    }
}

void ThReceiverClient::setGameModel(GameModelClient* gameModel){
    _gameModel = gameModel;
}

GameModelClient* ThReceiverClient::getGameModel(){
    return _gameModel;
}

ThReceiverClient::~ThReceiverClient(){
}
