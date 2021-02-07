#include "UserClient.h"

#include "GameModelClient.h"

#include <chrono>
#include <iostream>
#include <sys/time.h>

UserClient::UserClient(ThSender& th_sender, GameModelClient& game_model,int &_winner_id, bool& game_done,\
    std::vector<std::pair<int,int>> &_ordered_players_kills, std::vector<std::pair<int,int>> &_ordered_players_points,\
    std::vector<std::pair<int,int>> &_ordered_players_bullets):
        th_sender(th_sender), _game_model(game_model), _background_music(),
        _winner_id(_winner_id), game_done(game_done),_ordered_players_kills(_ordered_players_kills),
        _ordered_players_points(_ordered_players_points),_ordered_players_bullets(_ordered_players_bullets){
    game_done = false;
}

// Hacer todo para empezar a jugar la partida.
void UserClient::play(){
    gameLoop();
    endGame();
}

void UserClient::endGame(){
    printf("TOY EN EL ENDGAME WACHINNNNN\n");

    int position = 1;
    if (_winner_id != -1){
        std::cout << "The winner is Player ID: " << _winner_id << std::endl;
    } else {
        std::cout << "TIME IS OVER\n";
    }
    for (auto& player : _ordered_players_kills){
        std::cout << "Position " << position << " Player_ID: " << player.second << " Kills: " << player.first << std::endl;
        ++position;
    }
    position = 1;
    for (auto& player : _ordered_players_points){
        std::cout << "Position " << position << " Player_ID: " << player.second << " Points: " << player.first << std::endl;
        ++position;
    }
    position = 1;
    for (auto& player : _ordered_players_bullets){
        std::cout << "Position " << position << " Player_ID: " << player.second << " Bullets: " << player.first << std::endl;
        ++position;
    }

    Screen screen(_game_model.getScreen());

    bool player_won = (_game_model.getPlayer().getId() == _winner_id);

    screen.showEndgame(player_won,_winner_id, game_done, _ordered_players_kills,_ordered_players_points,_ordered_players_bullets);
    SDL_Event event;
    game_done = false;
    while(!game_done){
        while (SDL_PollEvent(&event)) { 
            switch(event.type) {
                case SDL_QUIT: {
                    game_done = SDL_TRUE;
                }
            }
        }
    }
}

void UserClient::getKeys(const Uint8 *keys, SDL_Event &event, Protocol &protocol, Player& player, int &frames_till_next_shot, bool &shoot_key_pressed, int &repetition_key_delay){
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
    if(keys[SDL_SCANCODE_M] and !repetition_key_delay){
        _background_music.togglePause();
        repetition_key_delay = 5;
    }else{
    	if(repetition_key_delay>0)
    	repetition_key_delay--;
    }

    if(keys[SDL_SCANCODE_RCTRL] or keys[SDL_SCANCODE_LCTRL]){
        if(frames_till_next_shot==0){
        	if(!shoot_key_pressed or (shoot_key_pressed and player.gunAllowsContinuousShooting())){
	        	frames_till_next_shot = player.getFramesPerShot();
	            protocol.setAction(
	                Protocol::action::SHOOT);
	            th_sender.push(protocol);
	        }
        }
        shoot_key_pressed = true;
    }else{
    	shoot_key_pressed = false;
    }
    if(keys[SDL_SCANCODE_SPACE]){
        protocol.setAction(
            Protocol::action::OPEN);
        th_sender.push(protocol);
        showPlayersInfo(player);
    }
    if(keys[SDL_SCANCODE_0] || keys[SDL_SCANCODE_KP_0]){
        protocol.setAction(
            Protocol::action::SWITCH_GUN);
        protocol.setDamage(0);
        th_sender.push(protocol);
    }
    if(keys[SDL_SCANCODE_1] || keys[SDL_SCANCODE_KP_1]){
        protocol.setAction(
            Protocol::action::SWITCH_GUN);
        protocol.setDamage(1);
        th_sender.push(protocol);
    }
    if(keys[SDL_SCANCODE_2] || keys[SDL_SCANCODE_KP_2]){
        protocol.setAction(
            Protocol::action::SWITCH_GUN);
        protocol.setDamage(2);
        th_sender.push(protocol);
    }
    if(keys[SDL_SCANCODE_3] || keys[SDL_SCANCODE_KP_3]){
        protocol.setAction(
            Protocol::action::SWITCH_GUN);
        protocol.setDamage(3);
        th_sender.push(protocol);
    }
    if(keys[SDL_SCANCODE_4] || keys[SDL_SCANCODE_KP_4]){
        protocol.setAction(
            Protocol::action::SWITCH_GUN);
        protocol.setDamage(4);
        th_sender.push(protocol);
    }

    while (SDL_PollEvent(&event)) { 
        switch(event.type) {
            case SDL_QUIT: {
                game_done = SDL_TRUE;
            }
        }
    }
}

void UserClient::gameLoop(){
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

    Player& player = _game_model.getPlayer();

    const Uint8 *keys = SDL_GetKeyboardState(NULL);    

    int frames_till_next_shot = 0;
    bool shoot_key_pressed = false;
    int repetition_key_delay = 0;

    while (!game_done) {
        gettimeofday(&time_now, nullptr);
        time_t time = (time_now.tv_usec / 1000);

        getKeys(keys, event, protocol, player, frames_till_next_shot, shoot_key_pressed, repetition_key_delay);

        _game_model.run();//Proceso los protocolos

        _game_model.updateFrameAnimations();
        if(frames_till_next_shot>0)
        	frames_till_next_shot--;

        screen.show();
        _background_music.playMusic();
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
//    _game_model.hideWindow();
    std::cout<<"El maximo fue: "<<max_time<<std::endl;
    std::cout<<"El tiempo promedio fue:"<<total_time/counter<<std::endl;
}

void UserClient::showPlayersInfo(Player& player){
    auto players = _game_model.getCharacters();
    for(auto& it : players){
        auto player = it.second;
        std::cout << "Player:   " << player->getId() << std::endl;
        std::cout << "Posicion:  X: " << player->get_position().x << " Y: " << player->get_position().y  << std::endl;
        std::cout << "Direccion: X: " << player->getDirection().x << " Y: " << player->getDirection().y << std::endl;
        std::cout << "\n-------------------------------------------------------------------\n";
    }
}

void UserClient::stop(){
    game_done = SDL_TRUE;
}

UserClient::~UserClient(){
}
