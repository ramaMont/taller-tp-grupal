#ifndef __TH_USER_CLIENT__
#define __TH_USER_CLIENT__

#include "ThSender.h"
#include "BackgroundMusic.h"

class GameModelClient;
#include "GameModelClient.h"
#include "Screen.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Player.h"

class UserClient{
private:
    ThSender& th_sender;
    GameModelClient& _game_model;
    BackgroundMusic _background_music;

    int &_winner_id;
    bool& game_done;
    std::vector<std::pair<int,int>> &_ordered_players_kills;
    std::vector<std::pair<int,int>> &_ordered_players_points;
    std::vector<std::pair<int,int>> &_ordered_players_bullets;

    void getKeys(const Uint8 *keys, SDL_Event &event, Protocol &protocol, Player& player, int &frames_till_next_shot, bool &shoot_key_pressed, int &repetition_key_delay);

    void gameLoop(Screen& screen);
    void endGame(Screen& screen);
public:
    explicit UserClient(ThSender& th_sender, GameModelClient& game_model,int &_winner_id, bool& game_done,\
    std::vector<std::pair<int,int>> &_ordered_players_kills, std::vector<std::pair<int,int>> &_ordered_players_points,\
    std::vector<std::pair<int,int>> &_ordered_players_bullets);
    void play();
    void stop();
    void showPlayersInfo(Player& player);
    ~UserClient();
};

#endif
