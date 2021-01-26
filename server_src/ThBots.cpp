#include "ThBots.h"

#include <ThGameModelServer.h>
#include <thread>
#include <chrono>
#include <iostream>

#define TIME_SLEEP 200

ThBots::ThBots(ThGameModelServer* th_game_model,
               BlockingQueue<Protocol>& game_model_queue,
               std::map<int,Player*>& players,
               const Mapa& map,
               int number_of_bots):
    Thread(),
    players(players),
    _game_model_queue(game_model_queue),
    number_of_bots(number_of_bots),
    th_game_model(th_game_model),
    map(map){
    is_running = true;
}

void ThBots::run(){
    if (number_of_bots <= 0)
        return;
//    addBots();
    while (is_running){
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME_SLEEP));
        for (auto it = bots.begin(); it != bots.end() && is_running; ++it){
            try{
                Player* player = players[it->first];
player->cambiarArma(N_CUCHILLO);  // Eliminar linea
                Bot::Event event = it->second->getEvent(player, players);
                makeEvent(it->first, event);
            } catch(...) { }
        }
    }
}

void ThBots::stop(){
    is_running = false;
}

void ThBots::addBots(){
    if (number_of_bots <= 0)
        return;
    int bots_added = 0;
    for (int player_id = 0; player_id < 100; ++player_id){
        if (players.count(player_id) > 0)
            continue;

        th_game_model->addPlayer(player_id);
        Bot* bot = new Bot(map);
        bots[player_id] = bot;   

        // Copiado de GamesAdmin::joinGame
        // Le envio a todos los jugadores que se ha unido uno nuevo.
        // int map_id_checksum = th_game_model->getMapIdChecksum();
        // Coordinates player_direction = th_game_model->getPlayer(player_id).
        //         get_direction();
        // Coordinates player_position = th_game_model->getPlayer(player_id).
        //         get_coordinates();
        // Protocol::direction prot_direction = player_direction.
        //         cast_to_direction();
        // Protocol protocol_response(Protocol::action::ADD_PLAYER,
        //                            player_id, prot_direction, map_id_checksum,
        //                            player_position.x, player_position.y);
        // th_game_model->echoProtocol(protocol_response);
 
        bots_added++;
        if (bots_added == number_of_bots)
            return;
    }
}

void ThBots::makeEvent(int player_id, Bot::Event event){
    switch (event){
    case Bot::Event::MoverAdelante:{
        Protocol p(player_id);
        p.setAction(Protocol::action::MOVE);
        p.moveInDirection(Protocol::direction::FORWARD);
        _game_model_queue.push(p);
        break;
    }
    case Bot::Event::MoverIzquierda:{
        Protocol p(player_id);
        p.setAction(Protocol::action::MOVE);
        p.moveInDirection(Protocol::direction::ROTATE_LEFT);
        _game_model_queue.push(p);
        break;
    }
    case Bot::Event::MoverDerecha:{
        Protocol p(player_id);
        p.setAction(Protocol::action::MOVE);
        p.moveInDirection(Protocol::direction::ROTATE_RIGHT);
        _game_model_queue.push(p);
        break;
    }
    case Bot::Event::Disparar:{
        Protocol p(player_id);
        p.setAction(Protocol::action::SHOOT);
        _game_model_queue.push(p);
        break;
    }
    case Bot::Event::CambiarArmaCuchillo:{
        break;
    }
    case Bot::Event::AbrirPuerta:{
        break;
    }
    }
}

ThBots::~ThBots(){
    for (auto it = bots.begin(); it != bots.end(); ++it){
        delete(it->second);
    }
}

