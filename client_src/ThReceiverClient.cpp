#include "ThReceiverClient.h"
#include <iostream>

#include "GameModelClient.h"
#include <SocketException.hpp>

ThReceiverClient::ThReceiverClient(Socket* socket, ClientHolder& client_holder,
        GameModelClient* game_model_client):
        ThReceiver(socket), _client_holder(client_holder), 
        _gameModel(game_model_client){
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
    if (protocol.getAction() == Protocol::action::BEGIN){
        _client_holder.startGame();
    } else if (protocol.getAction() == Protocol::action::ADD_PLAYER){
        _gameModel->addPlayer(protocol);
    } else if (protocol.getAction() == Protocol::action::ADD_PLAYER){
        _gameModel->removeEnemy(protocol.getUserId());
    } else {
        // Cualquier otro tipo de protocolo:
        _gameModel->push(protocol);
    }
}

ThReceiverClient::~ThReceiverClient(){
}
