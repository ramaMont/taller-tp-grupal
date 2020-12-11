#include "ThUserClient.h"

#include <iostream>
#include <Mapa.h>
#include <vector>
#include <map>
#include <GameModel.h>
#include <ThKeyReader.h>
#include <ThDrawer.h>

ThUserClient::ThUserClient(int user_id, ThReceiver& th_receiver, ThSender& th_sender):
    ThUser(user_id), th_receiver(th_receiver), th_sender(th_sender), _game_model(nullptr){
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
                Protocol protocol;
                protocol.setAction(Protocol::action::LAUNCH_GAME);
                th_sender.push(protocol);
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
    ThDrawer th_drawer(th_receiver.getGameModel()->getPlayer(user_id),
        th_receiver.getGameModel()->getMap());
    ThKeyReader th_key_reader(th_sender);
    th_drawer.start();
    th_key_reader.start();
    th_key_reader.join();
    th_drawer.stop();
    th_drawer.join();
}

void ThUserClient::createGameModel(int map_id){
    Mapa map(24,24);
    Coordinates initial_position(2.5, 2.5);
    Coordinates initial_direction(0, 1);
    Player player(initial_position, initial_direction, map, user_id);
    std::map<int,Player> players;
    players.insert(std::pair<int,Player>(user_id, player));
    initMap(map);
    _game_model = new GameModelClient(std::move(map), std::move(players));
    th_receiver.setGameModel(_game_model);
}

void ThUserClient::processReception(Protocol& protocol){
    switch (protocol.getAction()){
        case Protocol::action::OK:
            createGameModel(protocol.getId());
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
    if (_game_model != nullptr)
        delete(_game_model);
}
