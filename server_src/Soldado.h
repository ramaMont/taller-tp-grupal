#ifndef __SOLDADO__
#define __SOLDADO__

#include <set>
#include <vector>
#include <atomic>
#include <map>
#include "coordinates.h"
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
	virtual int throwGun(Player *player) = 0;
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
	int throwGun(Player *player) override;
	bool ready() override;
	int gunNumber() const;
};


class Guard: public Soldier {
	public:
	Guard(int& bullets);
	int shoot(Player *player, std::map<int, Player*>&) override;
	int throwGun(Player *player) override;
	bool ready() override;
	int gunNumber() const;
};


class SS: public Soldier {
	public:
	SS(int &bullets);
	int shoot(Player *player, std::map<int, Player*>&) override;	
	int throwGun(Player *player) override;
	bool ready() override;
	int gunNumber() const;
};


class Officer: public Soldier {
	public:
	Officer(int &bullets);
	int shoot(Player *player, std::map<int, Player*>&) override;
	int throwGun(Player *player) override;
	bool ready() override;
	int gunNumber() const;
};


class Mutant: public Soldier {
	public:
	Mutant(int &bullets);
	int shoot(Player *player, std::map<int, Player*>&) override;	
	int throwGun(Player *player) override;
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
	
	public:
	explicit SoldierState(Player *player, int& bullets);
	int actualGun();
	bool addGun(int gun_number);
	void switchGun(int gun_number);
	int throwGun();
	int shoot(std::map<int, Player*>& enemies);
	void rechargeBullets();
};


#endif
