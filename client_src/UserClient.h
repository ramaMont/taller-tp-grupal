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

#include <utility>
#include <vector>

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

    bool& player_alive;

    bool game_canceled;
    bool& _have_winner;

    void pollEvents(SDL_Event& event, Window& window);

    void getKeys(const Uint8 *keys, SDL_Event &event, Protocol &protocol, 
        Player& player, int &frames_till_next_shot, 
        bool &shoot_key_pressed, int &repetition_key_delay, Window& window);

    void gameLoop(SDL_Event& event, Screen& screen, Player& player, 
        Window& window);
    void endGame(SDL_Event& event, Screen& screen, Player& player, 
        Window& window);

    void getKeysToServer(const Uint8 *keys, SDL_Event &event, 
        Protocol &protocol, Player& player, int &frames_till_next_shot,
        bool &shoot_key_pressed);

    void getKeysPlayerDead(const Uint8 *keys, Player& player);

public:
    explicit UserClient(ThSender& th_sender, GameModelClient& game_model,\
        int &_winner_id, bool& game_done,\
        std::vector<std::pair<int,int>> &_ordered_players_kills,\
        std::vector<std::pair<int,int>> &_ordered_players_points,\
        std::vector<std::pair<int,int>> &_ordered_players_bullets,\
        bool& player_alive, bool& have_winner);
    void play();
    void stop();
    ~UserClient();
};

#endif
