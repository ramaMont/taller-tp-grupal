#ifndef __TH_USER_CLIENT__
#define __TH_USER_CLIENT__

#include "ThSender.h"

class GameModelClient;
#include "GameModelClient.h"


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Jugador.h"

class UserClient{
private:
    ThSender& th_sender;
    GameModelClient& _game_model;

    void get_keys(const Uint8 *keys, SDL_Event &event, Protocol &protocol, SDL_bool &done, Jugador& jugador);

    void gameLoop();
public:
    explicit UserClient(ThSender& th_sender, GameModelClient& game_model);
    void play();
    ~UserClient();
};

#endif
