#ifndef __GAME_MODEL_CLIENT__
#define __GAME_MODEL_CLIENT__

#include "UserClient.h"
#include <Protocol.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ClMap.h"
#include "Protocol.h"
#include "Player.h"
#include "BlockingQueue.h"

#include <atomic>
#include <map>
#include <vector>
#include <utility>

#include <Posicionable.h>

#include "window.h"
#include "Screen.h"
#include "texture.h"

#include <ClMap.h>
#include <coordinates.h>
#include <Character.h>
#include <Player.h>
#include <Cl_Direction.h>
#include <Wall.h>
#include <Door.h>
#include <SpriteHolder.h>
#include <Enemy.h>
#include <Rocket.h>
#include "SoundPlayer.h"

#include "CharacterValues.h"

class GameModelClient {
private:
        WallGreystone wallGreystone;
        std::vector<WallGreystone> wallsGreystone;

    Window window;	
    Texture texture;
    ClMap map; 	
	bool added_player;
    Player player;	
	std::queue<Protocol> operations;
    std::map<int,Character*> characters;
    std::map<Protocol::direction, Direction* > directions;
    int game_id;
    Screen screen;
    int protagonist_id;

    std::vector<Wall*> walls;
    std::vector<Door*> doors;
    std::vector<SpriteHolder*> sprites;
    std::vector<Enemy*> enemies;
    std::vector<Rocket*> rockets;

	bool is_running;
    SoundPlayer _sound_player;
    bool _has_ended;

    int &_winner_id;
    bool& game_done;
    std::vector<std::pair<int,int>> &_ordered_players_kills;
    std::vector<std::pair<int,int>> &_ordered_players_points;
    std::vector<std::pair<int,int>> &_ordered_players_bullets;

    void addWall(std::string type, Coordinates position);

    void updateEvent();
    void move(int player_id);
    void shoot();
    void processMove(Protocol& protocol);
    void initMap(std::string map_filename);
    void initDirections();
    void cleanDirections();

    void processShoot(Protocol protocol);
    void processShooted(Protocol protocol);
    void processPickup(Protocol& protocol);
    void processThrow(Protocol& protocol);
    void processGunSwitch(Protocol& protocol);
    void processRocket(Protocol& protocol);
    void processExplosion(Protocol& protocol);
    void processKey(Protocol& protocol);
    void openDoor(const Protocol& protocol);
    void openingDoor(const Protocol& protocol);
    void closeDoor(const Protocol& protocol);
    float calculateDistanceBetween(Posicionable* positionable);
    void playSound(SoundPlayer::sound_type sound_type, Posicionable* positionable);
    void endGame();
    void waitForAction(Protocol::action desired_action);
    void addDeadSprite(Coordinates position, CharacterType a_character_type);

    void removeCharacterFromMap(int id);
public:
    explicit GameModelClient(int user_id, std::string map_filename, int game_id, int protagonist_id,int &_winner_id, bool& game_done,\
    std::vector<std::pair<int,int>> &_ordered_players_kills, std::vector<std::pair<int,int>> &_ordered_players_points,\
    std::vector<std::pair<int,int>> &_ordered_players_bullets);

    virtual void processProtocol(Protocol& protocol);
    void run();
    virtual void push(Protocol protocol);
    void removePlayer(int user_id);
    
    void stop();
    //void push(Protocol protocol);
    //virtual void processProtocol(Protocol& protocol) = 0;


    void player_shoot();

    void showWindow();

    void hideWindow();

    void addPlayer(Protocol& protocol);
    Player& getPlayer();
    Window& getWindow();
    Screen& getScreen();
    Character& getEnemy(int user_id);
    void updateFrameAnimations();


    ClMap& getMap();
    int getId();
    std::map<int,Character*> getCharacters();

    GameModelClient(const GameModelClient&) = delete;
    GameModelClient(GameModelClient&& other) = delete;
    GameModelClient& operator=(const GameModelClient&) = delete;
    GameModelClient& operator=(GameModelClient&& other);
    virtual ~GameModelClient();

};

#endif
