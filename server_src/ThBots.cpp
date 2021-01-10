#include "ThBots.h"

#include <ThGameModelServer.h>
#include <thread>
#include <chrono>

#define TIME_SLEEP 500

ThBots::ThBots(ThGameModelServer* th_game_model,
               BlockingQueue<Protocol>& game_model_queue,
               std::map<int,Player*>& players,
               const Mapa& mapa,
               int number_of_bots):
    Thread(),
    players(players),
    _game_model_queue(game_model_queue){
    is_running = true;
    int last_id = players.size();
    for (int player_id=last_id; player_id<last_id+number_of_bots; ++player_id){
        th_game_model->addPlayer(player_id);
        Bot* bot = new Bot(mapa);
        bots[player_id] = bot;   

        // Copiado de GamesAdmin::joinGame
        // Le envio a todos los jugadores que se ha unido uno nuevo.
        // Incluido el nuevo jugador asi se agrega en su modelo.
        Protocol protocol(player_id);   // No se si esta bien
        protocol.setAction(Protocol::action::ADD_PLAYER);
        th_game_model->echoProtocol(protocol);
    }
}

void ThBots::run(){
    while (is_running){
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME_SLEEP));
        for (auto it = bots.begin(); it != bots.end() && is_running; ++it){
            try{
                Player* player = players[it->first];
                Bot::Event event = it->second->getEvent(player, players);
                makeEvent(it->first, event);
            } catch(...) { }
        }
    }
}

void ThBots::stop(){
    is_running = false;
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

