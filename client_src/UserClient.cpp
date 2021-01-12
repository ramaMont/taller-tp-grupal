#include "UserClient.h"

#include "Cl_Mapa.h"
#include "GameModelClient.h"

#include <chrono>
#include <iostream>
#include <sys/time.h>

UserClient::UserClient(ThSender& th_sender, GameModelClient& game_model):
    th_sender(th_sender), _game_model(game_model){
}

// Hacer todo para empezar a jugar la partida.
void UserClient::play(){
    gameLoop();
}

void UserClient::get_keys(const Uint8 *keys, SDL_Event &event, Protocol &protocol, SDL_bool &done,Jugador& jugador){
    if(keys[SDL_SCANCODE_RIGHT]){
        protocol.moveInDirection(
            Protocol::direction::ROTATE_RIGHT);
        th_sender.push(protocol);
    }
    if(keys[SDL_SCANCODE_LEFT]){
        protocol.moveInDirection(
            Protocol::direction::ROTATE_LEFT);
        th_sender.push(protocol);
    }
    if(keys[SDL_SCANCODE_UP]){
        protocol.moveInDirection(
            Protocol::direction::FORWARD);
        th_sender.push(protocol);
    }
    if(keys[SDL_SCANCODE_DOWN]){
        protocol.moveInDirection(
            Protocol::direction::BACKWARD);
        th_sender.push(protocol);
    }

    if(keys[SDL_SCANCODE_RCTRL] or keys[SDL_SCANCODE_LCTRL]){
        if(jugador.can_shoot()){
            protocol.setAction(
                Protocol::action::SHOOT);
            th_sender.push(protocol);
        }
    }else{
        //player.stopped_shooting();
    }
    while (SDL_PollEvent(&event)) { 
        switch(event.type) {
            case SDL_QUIT: {
                done = SDL_TRUE;
            }
        }
    }
}

void UserClient::gameLoop(){
    SDL_bool done = SDL_FALSE;
    _game_model.showWindow();
    Screen screen(_game_model.getScreen());
    int id = th_sender.getId();
    Protocol protocol(id);
    SDL_Event event;

    time_t rate = 1000/30;

    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    time_t total_time = 0;
    time_t counter = 0;
    time_t max_time = 0;

    Jugador& jugador = _game_model.getPlayer();

    const Uint8 *keys = SDL_GetKeyboardState(NULL);    
    while (!done) {
        gettimeofday(&time_now, nullptr);
        time_t time = (time_now.tv_usec / 1000);

        get_keys(keys, event, protocol, done, jugador);

        _game_model.run();//Proceso los protocolos

        _game_model.updateFrameAnimations();

        screen.show();

        gettimeofday(&time_now, nullptr);
        time_t new_time = (time_now.tv_usec / 1000);

        time_t rest;
        if(new_time>time)
            rest = new_time - time;
        else
            rest = new_time - time + 1000;


        if(rest>max_time)
            max_time = rest;

        total_time+=rest;
        counter++;

        std::this_thread::sleep_for(std::chrono::milliseconds(rate - rest));
    }
    _game_model.hideWindow();
    std::cout<<"El maximo fue: "<<max_time<<std::endl;
    std::cout<<"El tiempo promedio fue:"<<total_time/counter<<std::endl;
}

UserClient::~UserClient(){
}
