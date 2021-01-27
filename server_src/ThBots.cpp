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
    uint16_t current_bot_id = -1;
    for (int bots_added = 0; bots_added < number_of_bots; ++bots_added){

        th_game_model->addPlayer(current_bot_id);
        Bot* bot = new Bot(map);
        bots[current_bot_id] = bot;   

        --current_bot_id;
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

