#include "ThBots.h"

#include <ThGameModelServer.h>

#include <thread>
#include <chrono>
#include <iostream>
#include <map>
#include <sys/time.h>

#define TIME_SLEEP 200

ThBots::ThBots(ThGameModelServer* th_game_model,
               BlockingQueue<Protocol>& game_model_queue,
               std::map<int,Player*>& players,
               const ServerMap& map,
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
    
    time_t rate = TIME_SLEEP;
    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    
    while (is_running){
        gettimeofday(&time_now, nullptr);
        time_t time = (time_now.tv_usec / 1000);

        for (auto it = bots.begin(); it != bots.end() && is_running; ++it){
            try{
                Player* player = players[it->first];
                if (player->isAlive()){
                    Bot::Event event = it->second->getEvent(player, players);
                    makeEvent(it->first, event);
                }
            } catch(...) { }
        }        
        
        gettimeofday(&time_now, nullptr);
        time_t new_time = (time_now.tv_usec / 1000);
        time_t rest = new_time - time;
        std::this_thread::sleep_for(std::chrono::milliseconds(rate - rest));
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
        case Bot::Event::MoveForward:{
            Protocol p(player_id);
            p.setAction(Protocol::action::MOVE);
            p.moveInDirection(Protocol::direction::FORWARD);
            _game_model_queue.push(p);
            break;
        }
        case Bot::Event::RotateLeft:{
            Protocol p(player_id);
            p.setAction(Protocol::action::MOVE);
            p.moveInDirection(Protocol::direction::ROTATE_LEFT);
            _game_model_queue.push(p);
            break;
        }
        case Bot::Event::RotateRight:{
            Protocol p(player_id);
            p.setAction(Protocol::action::MOVE);
            p.moveInDirection(Protocol::direction::ROTATE_RIGHT);
            _game_model_queue.push(p);
            break;
        }
        case Bot::Event::Shoot:{
            Protocol p(player_id);
            p.setAction(Protocol::action::SHOOT);
            _game_model_queue.push(p);
            break;
        }
        case Bot::Event::SwitchToKnife:{
            Protocol p(player_id);
            p.setAction(Protocol::action::SWITCH_GUN);
            p.setDamage(0);
            _game_model_queue.push(p);
            break;
        }
        case Bot::Event::OpenDoor:{
	        Protocol p(player_id);
	        p.setAction(Protocol::action::OPEN);
            _game_model_queue.push(p);
            break;
        }
	    case Bot::Event::Nothing:{
            break;
        }
    }
}

ThBots::~ThBots(){
    for (auto it = bots.begin(); it != bots.end(); ++it){
        delete(it->second);
    }
}

