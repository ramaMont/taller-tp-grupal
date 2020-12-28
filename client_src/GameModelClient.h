#ifndef __GAME_MODEL_CLIENT__
#define __GAME_MODEL_CLIENT__

#include "UserClient.h"
#include <Protocol.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Cl_Mapa.h"
#include "Protocol.h"
#include "Jugador.h"
#include "BlockingQueue.h"

#include <atomic>
#include <map>
#include <vector>

#include <Posicionable.h>

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

class GameModelClient {
private:
    Window window;	
    Texture texture;
    Cl_Mapa map; 	
	bool added_player;
    Jugador player;	
	std::queue<Protocol> operations;
    std::vector<int> id_insertion_order;
    std::map<int,Movable*> movables;
    std::map<Protocol::direction, Direccion* > directions;
    int game_id;
    Screen screen;
    int protagonist_id;

    std::vector<Sprite_drawer*> sprites;
    std::vector<Enemy*> enemies;

	bool is_running;

    void updateEvent();
    void move(int player_id);
    void shoot();
    void processMove(Protocol& protocol);
    void initMap();
    void initDirections();
    void cleanDirections();

public:
    explicit GameModelClient(int user_id, int map_id, int game_id, int protagonist_id);

    virtual void processProtocol(Protocol& protocol);
    void run();
    virtual void push(Protocol protocol);
    void removePlayer(int user_id);
    
    void stop();
    //void push(Protocol protocol);
    //virtual void processProtocol(Protocol& protocol) = 0;

    void addPlayer(int player_id);
    Jugador& getPlayer();
    Window& getWindow();
    Screen& getScreen();
    Movable& getEnemy(int user_id);
    void updateEnemyFrames();


    Cl_Mapa& getMap();
    int getId();

    std::vector<int>& getIdsVector();

    GameModelClient(const GameModelClient&) = delete;
    GameModelClient(GameModelClient&& other) = delete;
    GameModelClient& operator=(const GameModelClient&) = delete;
    GameModelClient& operator=(GameModelClient&& other);
    virtual ~GameModelClient();


};

#endif
