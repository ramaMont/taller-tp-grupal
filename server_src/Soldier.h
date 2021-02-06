#ifndef __SOLDIER__H_
#define __SOLDIER__H_

#include <set>
#include <vector>
#include <atomic>
#include <map>
#include "coordinates.h"
#include "BlockingQueue.h"
#include "Protocol.h"
class Mapa;
class Player;

enum GunNumber{
    KNIFE = 0,
    GUN,
    MACHINE_GUN,
    CANON_GUN,
    ROCKET_GUN
};


class Soldier {
	protected:
	int &bullets;
    bool gun;

    public:
    Soldier(int &bullets): bullets(bullets), gun(true) { }
	virtual int shoot(Player *player, std::map<int, Player*>&) = 0;
	virtual int throwGun(Mapa& map, const Coordinates& position) = 0;
	virtual bool ready() = 0;
	virtual int gunNumber() const = 0;
	bool addGun();
    void getCloserEnemies(std::map<int, Player*>& enemies,
       Player* player, std::set<std::pair<int, Player*>>& players);
    void tryShoot(Player* player, std::set<std::pair<int, Player*>>& enemies, float precision);
    bool crashes(Mapa& map, const Coordinates& start, const Coordinates& end);
    void atack(Player* player, Player* enemy, float precision, int angle);
    bool fireBullet(Player* player, float precision, int angle, Player* enemy);
};



class Dog: public Soldier {
	public:
	Dog(int& n);
	int shoot(Player *player, std::map<int, Player*>&) override;
	void bite(Player* player, std::set<std::pair<int, Player*>>& enemies);
	int throwGun(Mapa& map, const Coordinates& position) override;
	bool ready() override;
	int gunNumber() const;
};


class Guard: public Soldier {
	public:
	Guard(int& bullets);
	int shoot(Player *player, std::map<int, Player*>&) override;
	int throwGun(Mapa& map, const Coordinates& position) override;
	bool ready() override;
	int gunNumber() const;
};


class SS: public Soldier {
	public:
	SS(int &bullets);
	int shoot(Player *player, std::map<int, Player*>&) override;	
	int throwGun(Mapa& map, const Coordinates& position) override;
	bool ready() override;
	int gunNumber() const;
};


class Officer: public Soldier {
	public:
	Officer(int &bullets);
	int shoot(Player *player, std::map<int, Player*>&) override;
	int throwGun(Mapa& map, const Coordinates& position) override;
	bool ready() override;
	int gunNumber() const;
};


class Mutant: public Soldier {
	public:
	Mutant(int &bullets);
	int shoot(Player *player, std::map<int, Player*>&) override;	
	int throwGun(Mapa& map, const Coordinates& position) override;
	bool ready() override;
	int gunNumber() const;
};



class SoldierState {
	private:
	Player *player;
	Soldier *soldier;
	Dog dog;
	Guard guard;
	SS ss;
	Officer officer;
	Mutant mutant;
	Soldier *last_soldier;
	std::atomic<int> actual_gun;
    BlockingQueue<Protocol>& game_model_queue;
	
	public:
	explicit SoldierState(Player *player, int& bullets,
        BlockingQueue<Protocol>& game_model_queue);
	int actualGun();
	bool addGun(int gun_number);
	void switchGun(int gun_number);
	int throwGun(const Coordinates& position);
	int shoot(std::map<int, Player*>& enemies);
	void rechargeBullets();
};


#endif
