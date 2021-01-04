#ifndef __TH_USER_CLIENT__
#define __TH_USER_CLIENT__

#include <Posicionable.h>
#include <ThUser.h>
#include "Protocol.h"
#include "BlockingQueue.h"
#include "ThSender.h"
class ClThReceiver;
#include "ClThReceiver.h"
class GameModelClient;
#include "GameModelClient.h"


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Jugador.h"

class UserClient{
private:
    ClThReceiver& th_receiver;
    ThSender& th_sender;
    GameModelClient* _th_game_model;
    bool is_creator;

    BlockingQueue<Protocol> operations;
    int user_id;    

    void joinOrCreateGame();
    void processReception(Protocol& protocol, bool& ready);
    void createGameModel(int map_id, int id_user_protocol, int game_id);
    void waitUntilLaunch();
    void play();

    void get_keys(const Uint8 *keys, SDL_Event &event, Protocol &protocol, SDL_bool &done, Jugador& jugador);

    void gameLoop();
public:
    explicit UserClient(int user_id, ClThReceiver& th_receiver, 
        ThSender& th_sender);
    virtual void run();

    void push(Protocol protocol);

    void stop();

    void waitForAction(Protocol::action desired_action);

    virtual void removePlayer(int user_id);
    ~UserClient();
};

#endif
