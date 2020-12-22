#include "ThUserClient.h"

#include <iostream>
#include <Mapa.h>
#include <vector>
#include <map>
#include <GameModel.h>
#include <ThKeyReader.h>
#include <ThDrawer.h>

ThUserClient::ThUserClient(int user_id, ThReceiver& th_receiver,
        ThSender& th_sender):
    ThUser(user_id), th_receiver(th_receiver), th_sender(th_sender),
    _th_game_model(nullptr), is_creator(false){
}

void ThUserClient::joinOrCreateGame(){
    int option_input;
    bool ready = false;
    while (!ready){
        std::cout << "Introduzca 1 para crear partida\n";
        std::cout << "Introduzca 2 unirse a una partida\n";
        std::cin >> option_input;
        switch (option_input){
            case 1:{
                int id_map;
                std::cout << "Introduzca el ID del mapa\n";
                std::cin >> id_map;
                Protocol protocol(id_map);
                protocol.setAction(Protocol::action::CREATE_GAME);
                th_sender.push(protocol);
                ready = true;
                is_creator = true;
                break;
            }
            case 2:{
                int game_id;
                std::cout << "Introduzca el ID de la partida\n";
                std::cin >> game_id;
                Protocol protocol(game_id);
                protocol.setAction(Protocol::action::JOIN_GAME);
                th_sender.push(protocol);
                ready = true;
                break;
            }
            default:
                std::cout << "Opcion incorrecta, intente nuevamente\n";
                break;
        }
    }
    ready = false;

    while (!ready){
        Protocol protocol = operations.pop();
        processReception(protocol, ready);
    }

    if (!is_creator){
        Protocol protocol = operations.pop();
        processReception(protocol, ready);
    }
    std::cout << "Esperando a iniciar la partida\n";
}

void ThUserClient::waitUntilLaunch(){
    int option_input;
    bool ready = false;
    while (!ready){
        std::cout << "Introduzca 1 para lanzar la partida\n";
        std::cin >> option_input;
        switch (option_input){
            case 1:{
                Protocol protocol(_th_game_model->getId());
                protocol.setAction(Protocol::action::LAUNCH_GAME);
                th_sender.push(protocol);
//                waitForAction(Protocol::action::OK);
                ready = true;
                break;
            }
            default:
                std::cout << "Opcion no valida\n";
                break;
        }
    }
}

void ThUserClient::processReception(Protocol& protocol, bool& ready){
    switch (protocol.getAction()){
        case Protocol::action::OK:
            createGameModel(protocol.getMapId(), user_id, protocol.getGameId());
            std::cout << "Partida creada\nId de Partida: " << 
                protocol.getGameId() << std::endl;
            ready = true;
            break;
        case Protocol::action::ADD_PLAYER:{
            if (_th_game_model == nullptr)
                createGameModel(protocol.getMapId(), protocol.getUserId(), 
                    protocol.getGameId());
            else
                _th_game_model->addPlayer(protocol.getUserId());
            break;
        }
        case Protocol::action::END:
            ready = true;
            break;
        case Protocol::action::ERROR:
            // TODO: algo salio mal.
            break;
        default:
            std::cout << "Nunca deberia entrar acá\n";
            // TODO: algo salio muy mal.
            break;
    }
}

void ThUserClient::createGameModel(int map_id, int id_user, int game_id){
    _th_game_model = new ThGameModelClient(id_user, map_id, game_id);
    th_receiver.setGameModel(_th_game_model);
}

// Hacer todo para empezar a jugar la partida.
void ThUserClient::play(){
    
    waitForAction(Protocol::action::BEGIN);

    ThDrawer th_drawer(th_receiver.getGameModel()->getPlayer(user_id),
        th_receiver.getGameModel()->getMap());
    ThKeyReader th_key_reader(th_sender);
    th_drawer.start();
    th_key_reader.start();
    _th_game_model->start();
    th_key_reader.join();
    th_drawer.stop();
    th_drawer.join();
    _th_game_model->join();
}

void ThUserClient::run(){
    joinOrCreateGame();
    if (is_creator)
        waitUntilLaunch();
    play();
}

void ThUserClient::removePlayer(int user_id){
    if (_th_game_model != nullptr){
        _th_game_model->removePlayer(user_id);
    }
}

ThUserClient::~ThUserClient(){
    if (_th_game_model != nullptr)
        delete(_th_game_model);
}
