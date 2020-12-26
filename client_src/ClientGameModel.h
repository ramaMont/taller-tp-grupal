#ifndef __CLIENT_GAME_MODEL__
#define __CLIENT_GAME_MODEL__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Cl_Mapa.h"
#include "Protocol.h"
#include "Jugador.h"
#include "BlockingQueue.h"

#include <atomic>
#include <map>
#include <vector>

#include "Cl_Posicionable.h"

#include "window.h"
#include "Screen.h"
#include "texture.h"

#include <Cl_Mapa.h>
#include <coordinates.h>
#include <Movable.h>
#include <Jugador.h>
#include <Cl_Direccion.h>
#include <Wall.h>
#include <Sprite_holder.h>
#include <Sprite_drawer.h>
#include <Enemy.h>

class ClientGameModel{
protected:
    Window window;	
    Texture texture;
    Cl_Mapa map; 	
	bool added_player;
    Jugador player;	
    BlockingQueue<Protocol> operations;
    std::vector<int> id_insertion_order;
    std::map<int,Movable*> movables;
    std::map<Protocol::direction, Direccion* > directions;
    int game_id;
    Screen screen;

    std::vector<Sprite_drawer*> sprites;
    std::vector<Enemy*> enemies;

    void updateEvent();
    void move(int player_id);
    void shoot();
    void processMove(Protocol& protocol);
    void initMap();
    void initDirections();
    void cleanDirections();

public:
    explicit ClientGameModel(int map_id, int game_id);

    Window& get_window();

    Screen& get_screen();

    void draw(SDL_bool &done);
    void run();
    void stop();
    //void push(Protocol protocol);
    //virtual void processProtocol(Protocol& protocol) = 0;

    virtual void push(Protocol protocol){
        operations.push(protocol);
    }

    void addPlayer(int player_id);
    Jugador& getPlayer();
    Movable& getEnemy(int user_id);

    void removePlayer(int id);

    Cl_Mapa& getMap();
    int getId();

    std::vector<int>& getIdsVector();

    ClientGameModel(const ClientGameModel&) = delete;
    ClientGameModel(ClientGameModel&& other) = delete;
    ClientGameModel& operator=(const ClientGameModel&) = delete;
    ClientGameModel& operator=(ClientGameModel&& other);
    virtual ~ClientGameModel();
};
#endif
