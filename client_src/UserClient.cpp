#include "UserClient.h"

#include "GameModelClient.h"

#include <chrono>
#include <iostream>
#include <sys/time.h>
#include <utility>
#include <vector>

UserClient::UserClient(ThSender& th_sender, GameModelClient& game_model,\
    int &_winner_id, bool& game_done,\
    std::vector<std::pair<int,int>> &_ordered_players_kills,\
    std::vector<std::pair<int,int>> &_ordered_players_points,\
    std::vector<std::pair<int,int>> &_ordered_players_bullets,\
    bool& player_alive, bool& have_winner):
        th_sender(th_sender), _game_model(game_model), _background_music(),
        _winner_id(_winner_id), game_done(game_done),
        _ordered_players_kills(_ordered_players_kills),
        _ordered_players_points(_ordered_players_points),
        _ordered_players_bullets(_ordered_players_bullets),
        player_alive(player_alive), game_canceled(false), 
        _have_winner(have_winner){
    game_done = false;
}

void UserClient::pollEvents(SDL_Event& event, Window& window){
    while (SDL_PollEvent(&event)) { 
        switch (event.type) {
            case SDL_QUIT: {
                game_done = SDL_TRUE;
                game_canceled = true;
            }
            case SDL_WINDOWEVENT:{
                if (event.window.event == SDL_WINDOWEVENT_RESIZED){
                    window.resizeWindow(event.window.data1, 
                        event.window.data2);
                }
            }
        }
    }
}

// Hacer todo para empezar a jugar la partida.
void UserClient::play(){
    Player& player = _game_model.getPlayer();
    Window& window = _game_model.getWindow();
    Screen &screen(_game_model.getScreen());
    SDL_Event event;
    gameLoop(event,screen, player, window);
    endGame(event,screen, player, window);
}

void UserClient::endGame(SDL_Event& event, Screen& screen, Player& player, 
        Window& window){
    bool player_won = (player.getId() == _winner_id);
    window.disableResizable();
    screen.showEndgame(player_won,_winner_id, game_done, game_canceled,
        _ordered_players_kills, _ordered_players_points, 
        _ordered_players_bullets, _have_winner);
    bool leave_ending_screen = false;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    while (!leave_ending_screen){
        if (keys[SDL_SCANCODE_ESCAPE]){
            leave_ending_screen = SDL_TRUE;
        }
	    while (SDL_PollEvent(&event)) { 
	        switch (event.type) {
	            case SDL_QUIT: {
	                leave_ending_screen = true;
	            }
	        }
	    }
    }
}

void UserClient::getKeysToServer(const Uint8 *keys, SDL_Event &event, 
        Protocol &protocol, Player& player, int &frames_till_next_shot,
        bool &shoot_key_pressed){
    if (keys[SDL_SCANCODE_RIGHT]){
        protocol.moveInDirection(
            Protocol::direction::ROTATE_RIGHT);
        th_sender.push(protocol);
    }
    if (keys[SDL_SCANCODE_LEFT]){
        protocol.moveInDirection(
            Protocol::direction::ROTATE_LEFT);
        th_sender.push(protocol);
    }
    if (keys[SDL_SCANCODE_UP]){
        protocol.moveInDirection(
            Protocol::direction::FORWARD);
        th_sender.push(protocol);
    }
    if (keys[SDL_SCANCODE_DOWN]){
        protocol.moveInDirection(
            Protocol::direction::BACKWARD);
        th_sender.push(protocol);
    }
    if (keys[SDL_SCANCODE_RCTRL] or keys[SDL_SCANCODE_LCTRL]){
        if (frames_till_next_shot==0){
            if(!shoot_key_pressed or player.gunAllowsContinuousShooting()){
                frames_till_next_shot = player.getFramesPerShot();
                protocol.setAction(Protocol::action::SHOOT);
                th_sender.push(protocol);
            }
        }
        shoot_key_pressed = true;
    } else {
        shoot_key_pressed = false;
    }
    if (keys[SDL_SCANCODE_SPACE]){
        protocol.setAction(
            Protocol::action::OPEN);
        th_sender.push(protocol);
    }
    if (keys[SDL_SCANCODE_0] || keys[SDL_SCANCODE_KP_0]){
        protocol.setAction(
            Protocol::action::SWITCH_GUN);
        protocol.setDamage(0);
        th_sender.push(protocol);
    }
    if (keys[SDL_SCANCODE_1] || keys[SDL_SCANCODE_KP_1]){
        protocol.setAction(
            Protocol::action::SWITCH_GUN);
        protocol.setDamage(1);
        th_sender.push(protocol);
    }
    if (keys[SDL_SCANCODE_2] || keys[SDL_SCANCODE_KP_2]){
        protocol.setAction(
            Protocol::action::SWITCH_GUN);
        protocol.setDamage(2);
        th_sender.push(protocol);
    }
    if (keys[SDL_SCANCODE_3] || keys[SDL_SCANCODE_KP_3]){
        protocol.setAction(
            Protocol::action::SWITCH_GUN);
        protocol.setDamage(3);
        th_sender.push(protocol);
    }
    if (keys[SDL_SCANCODE_4] || keys[SDL_SCANCODE_KP_4]){
        protocol.setAction(
            Protocol::action::SWITCH_GUN);
        protocol.setDamage(4);
        th_sender.push(protocol);
    }
}

void UserClient::getKeysPlayerDead(const Uint8 *keys, Player& player){
    if (keys[SDL_SCANCODE_RIGHT]){
        Direction* direction = new DirRotRight();
        player.moveDeadPosition(direction);
        delete direction;
    }
    if (keys[SDL_SCANCODE_LEFT]){
        Direction* direction = new DirRotLeft();
        player.moveDeadPosition(direction);
        delete direction;
    }
    if (keys[SDL_SCANCODE_UP]){
        Direction* direction = new DirForward();
        player.moveDeadPosition(direction);
        delete direction;
    }
    if (keys[SDL_SCANCODE_DOWN]){
        Direction* direction = new DirBackward();
        player.moveDeadPosition(direction);
        delete direction;
    }
}

void UserClient::getKeys(const Uint8 *keys, SDL_Event &event, 
        Protocol &protocol, Player& player, int &frames_till_next_shot,
        bool &shoot_key_pressed, int &repetition_key_delay,Window& window){

    if(player_alive){
        getKeysToServer(keys, event, protocol, player, 
            frames_till_next_shot,shoot_key_pressed);
    }else{
        getKeysPlayerDead(keys, player);
    }

    if (keys[SDL_SCANCODE_M] and !repetition_key_delay){
        _background_music.togglePause();
        repetition_key_delay = 5;
    } else {
    	if (repetition_key_delay>0)
    	repetition_key_delay--;
    }

    if (keys[SDL_SCANCODE_ESCAPE]){
        window.disableFullscreen();
    }
    pollEvents(event, window);
}

void UserClient::gameLoop(SDL_Event& event, Screen& screen, 
        Player& player, Window& window){
    _game_model.showWindow();
    int id = th_sender.getId();
    Protocol protocol(id);

    time_t rate = 1000/30;

    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    time_t total_time = 0;
    time_t max_time = 0;

    const Uint8 *keys = SDL_GetKeyboardState(NULL);    

    int frames_till_next_shot = 0;
    bool shoot_key_pressed = false;
    int repetition_key_delay = 0;

    while (!game_done) {
        gettimeofday(&time_now, nullptr);
        time_t time = (time_now.tv_usec / 1000);

        getKeys(keys, event, protocol, player, frames_till_next_shot,
            shoot_key_pressed, repetition_key_delay, window);

        _game_model.run();//Proceso los protocolos

        _game_model.updateFrameAnimations();
        if (frames_till_next_shot>0)
        	frames_till_next_shot--;

        screen.show();
        _background_music.playMusic();
        gettimeofday(&time_now, nullptr);
        time_t new_time = (time_now.tv_usec / 1000);
        time_t rest;
        if (new_time>time)
            rest = new_time - time;
        else
            rest = new_time - time + 1000;
        if (rest>max_time)
            max_time = rest;
        total_time+=rest;
        std::this_thread::sleep_for(std::chrono::milliseconds(rate - rest));
    }
}

void UserClient::stop(){
    game_done = SDL_TRUE;
}

UserClient::~UserClient(){
}
