#include "ThUserClient.h"

#include <iostream>
#include <Mapa.h>
#include <vector>
#include <map>
#include <GameModel.h>
#include <ThKeyReader.h>
#include <ThDrawer.h>

ThUserClient::ThUserClient(int user_id, ThReceiver& th_receiver, ThSender& th_sender):
    ThUser(user_id), th_receiver(th_receiver), th_sender(th_sender), _th_game_model(nullptr){
}

void ThUserClient::joinOrCreateGame(){
    int option_input;
    int id_map;
    bool ready = false;
    while (!ready){
        std::cout << "Introduzca 1 para crear partida\n";
        std::cout << "Introduzca 2 unirse a una partida\n";
        std::cin >> option_input;
        switch (option_input){
            case 1:{
                std::cout << "Introduzca el ID del mapa\n";
                std::cin >> id_map;
                Protocol protocol(id_map);
                protocol.setAction(Protocol::action::CREATE_GAME);
                th_sender.push(protocol);
                ready = true;
                break;
            }
            case 2:{
                std::cout << "Introduzca el ID de la partida\n";
                std::cin >> id_map;
                Protocol protocol(id_map);
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
        processReception(protocol);
        ready = true; 
    }
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

void ThUserClient::createGameModel(int map_id){
    _th_game_model = new ThGameModelClient(user_id, map_id, 0);
    th_receiver.setGameModel(_th_game_model);
}

void ThUserClient::processReception(Protocol& protocol){
    switch (protocol.getAction()){
        case Protocol::action::OK:
            createGameModel(protocol.getId());
            std::cout << "Partida creada\nId de Partida: " << 
                protocol.getId() << std::endl;
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

void ThUserClient::run(){
    joinOrCreateGame();
    waitUntilLaunch();
    play();
}

ThUserClient::~ThUserClient(){
    if (_th_game_model != nullptr)
        delete(_th_game_model);
}
