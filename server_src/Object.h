#ifndef __OBJECT__
#define __OBJECT__

#include "Posicionable.h"
#include "coordinates.h"
class Player;
#include "Player.h"
class ThGameModelServer;
class Mapa;
#include <map>
#define ROCKET_STEP 0.25

class Object: public Posicionable {
	public:
	Object(Coordinates coordinates): Posicionable(coordinates) { }
};


class Passage: public Object {
	public:
	Passage(Coordinates coordinates);
	bool open(Player *player);
};


class Door: public Object {
	private:
	bool has_event;
	std::atomic<bool> reopen;
	
	public:
	Door(Coordinates coordinates);
	virtual bool open(Player *player);
	bool openDoor(Player *player);
	std::atomic<bool>& getReopen();
	void letPass();
	void close();
};


class KeyDoor: public Door {
	private:
	bool opened = false;
	
	public:
	KeyDoor(Coordinates coordinates): Door(coordinates) { }
	bool open(Player *player) override;
};


class Rocket: public Object{
    private:
    Coordinates direction;
    Player* player;
    std::map<int, Player*>& enemies;
    Mapa& map;
    std::atomic<bool> exploded;

    public:
    Rocket(Coordinates position, Coordinates dir,Player* player,
        std::map<int, Player*>& enemies, ThGameModelServer& game_model);
    void move(ThGameModelServer& game_model);
    void explode();
    bool hasExploded();
    bool crashes(const Coordinates& start, const Coordinates& end);
    Coordinates getDirection();
    ~Rocket();
};

#endif
