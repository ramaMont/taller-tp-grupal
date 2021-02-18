#ifndef __GAME_MODEL_CLIENT__
#define __GAME_MODEL_CLIENT__

#include <Protocol.h>
#include <BlockingQueue.h>
#include <Protocol.h>
#include <Posicionable.h>
#include <GameModel.h>
#include <coordinates.h>
#include <Direction.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "UserClient.h"
#include "ClientMap.h"
#include "Player.h"
#include "window.h"
#include "Screen.h"
#include "texture.h"
#include "ClientMap.h"
#include "Character.h"
#include "Wall.h"
#include "Door.h"
#include "SpriteHolder.h"
#include "Enemy.h"
#include "Rocket.h"
#include "SoundPlayer.h"
#include "CharacterValues.h"

#include <atomic>
#include <map>
#include <vector>
#include <utility>
#include <queue>
#include <string>


class GameModelClient : public GameModel {
private:
    std::vector<WallGreystone> wallsGreystone;
    std::vector<WallBluestone> wallsBluestone;
    std::vector<WallPurplestone> wallsPurplestone;
    std::vector<WallColorstone> wallsColorstone;
    std::vector<WallEagle> wallsEagle;
    std::vector<WallMossy> wallsMossy;
    std::vector<WallRedbrick> wallsRedbrick;
    std::vector<WallWood> wallsWood;
    std::vector<Door> doors;

    Window window;	
    Texture texture;
    ClientMap map; 	
	bool added_player;
    Player player;	
	std::queue<Protocol> operations;
    std::map<int,Character*> characters;
    Screen screen;
    int protagonist_id;

    std::vector<SpriteHolder*> sprites;
    std::vector<Enemy*> enemies;
    std::vector<Rocket*> rockets;
    std::vector<SpriteHolder*> explosions;

	bool is_running;
    SoundPlayer _sound_player;
    bool _has_ended;

    int &_winner_id;
    bool& game_done;
    std::vector<std::pair<int,int>> &_ordered_players_kills;
    std::vector<std::pair<int,int>> &_ordered_players_points;
    std::vector<std::pair<int,int>> &_ordered_players_bullets;

    void addPositionableToMap(Posicionable& posicionable);

    void addWallsToMap();

    void createWall(const  std::string& type, Coordinates position);

    void addWall(const  std::string& type, Coordinates position);

    void updateEvent();
    void move(int player_id);
    void shoot();
    void processMove(Protocol& protocol);
    void initMap(const  std::string& map_filename);
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
    void playSound(SoundPlayer::sound_type sound_type, 
        Posicionable* positionable);
    void endGame();
    void waitForAction(Protocol::action desired_action);
    void addDeadSprite(Coordinates position, CharacterType a_character_type);

    void removeCharacterFromMap(int id);

    void addSpriteOn(Coordinates position, int sprite_value, bool add_explosion);

	void setDoorState(Coordinates door_pos, State new_state);

public:
    explicit GameModelClient(int user_id, const  std::string& map_filename, 
        int game_id, int protagonist_id,int &_winner_id, bool& game_done,\
        std::vector<std::pair<int,int>> &_ordered_players_kills,\
        std::vector<std::pair<int,int>> &_ordered_players_points,\
        std::vector<std::pair<int,int>> &_ordered_players_bullets,\
        int resolution_width, int resolution_height, bool fullscreen);

    void processProtocol(Protocol& protocol);
    void run();
    virtual void push(Protocol protocol) override;
    void removeEnemy(int user_id);
    
    void stop();

    void player_shoot();

    void showWindow();

    void hideWindow();

    void addPlayer(Protocol& protocol);

    Player& getPlayer();
    Window& getWindow();
    Screen& getScreen();
    Character& getEnemy(int user_id);
    void updateFrameAnimations();


    ClientMap& getMap();
    int getId();
    std::map<int,Character*> getCharacters();

    GameModelClient(const GameModelClient&) = delete;
    GameModelClient(GameModelClient&& other) = delete;
    GameModelClient& operator=(const GameModelClient&) = delete;
    GameModelClient& operator=(GameModelClient&& other);
    virtual ~GameModelClient();
};

#endif
