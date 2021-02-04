#ifndef __TH_USER_CLIENT__
#define __TH_USER_CLIENT__

#include "ThSender.h"
#include "BackgroundMusic.h"

class GameModelClient;
#include "GameModelClient.h"


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Player.h"

class UserClient{
private:
    ThSender& th_sender;
    GameModelClient& _game_model;
    bool done;
    BackgroundMusic _background_music;

    void getKeys(const Uint8 *keys, SDL_Event &event, Protocol &protocol, bool &done, Player& player, int &frames_till_next_shot, bool &shoot_key_pressed, int &repetition_key_delay);

    void gameLoop();
    void endGame();
public:
    explicit UserClient(ThSender& th_sender, GameModelClient& game_model);
    void play();
    void stop();
    void showPlayersInfo(Player& player);
    ~UserClient();
};

#endif
