#include "ThUser.h"
#include <iostream>
#include <Mapa.h>
#include <vector>
#include <map>
#include <GameModel.h>

// Pongo esta funcion global horrible aca, para inicializar los mapas de 
// manera momentanea.
void initMap(Mapa& map){
    std::vector<std::vector<int>> a_map{
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    for(int i=0; i<24; i++){
        for(int j=0; j<24; j++){
            if(a_map[i][j]!=0){
                Coordinates position((float)i,(float)j);
                Posicionable* posicionable = new Posicionable(position);
                map.agregarPosicionable(posicionable,position);
            }
        }
    }
}

ThUser::ThUser(int user_id, ThReceiver& th_receiver, ThSender& th_sender):
    Thread(), user_id(user_id), th_receiver(th_receiver), th_sender(th_sender){
}
void ThUser::run(){

    Protocol protocol = operations.pop();

}

void ThUser::push(Protocol protocol){
    operations.push(protocol);
}

int ThUser::getId(){
    return user_id;
}

void ThUser::stop(){
    is_running = false;
}

ThUser::~ThUser(){
}

ThUserClient::ThUserClient(int user_id, ThReceiver& th_receiver, ThSender& th_sender):
    ThUser(user_id, th_receiver, th_sender){
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
void ThUserClient::createGameModel(int map_id){
    Mapa map(24,24);
    Coordinates initial_position(2.5, 2.5);
    Coordinates initial_direction(0, 1);
    Player player(initial_position, initial_direction, map, user_id);
    std::map<int,Player *> players;
    players.insert(std::pair<int,Player *>(user_id, &player));
    initMap(map);
    GameModelClient* gameModel = new GameModelClient(std::move(map), std::move(players));
    th_receiver.setGameModel(gameModel);
}

void ThUserClient::processReception(Protocol& protocol){
    switch (protocol.getAction()){
        case Protocol::action::OK:
            createGameModel(protocol.getId());
            break;
        case Protocol::action::ERROR:

            break;
        default:
            std::cout << "Nunca deberia entrar acá\n";
            // TODO: algo salio muy mal.
            break;
    }
}

void ThUserClient::run(){
    joinOrCreateGame();
}


ThUserServer::ThUserServer(int user_id, ThReceiver& th_receiver, ThSender& th_sender):
    ThUser(user_id, th_receiver, th_sender){
}

void ThUserServer::run(){
    
}

ThUserClient::~ThUserClient(){
}

ThUserServer::~ThUserServer(){
}
