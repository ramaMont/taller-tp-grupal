#ifndef __SOLDADO__
#define __SOLDADO__

#include <set>
#include <vector>
#include <atomic>

enum GunNumber{
    KNIFE = 0,
    GUN,
    MACHINE_GUN,
    CANON_GUN,
    ROCKET_GUN
}


class Soldier {
	protected:
	int &bullets;

    public:
    Soldier(int &bullets): bullets(bullets) { }
	virtual int shoot(Player *player, std::map<int, Player*>&) = 0;
	virtual int throwGun(Player *player) = 0;
	virtual bool ready() = 0;
	virtual int actualGun() const = 0;
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
	void bite(Player* player, angulos_enemigos_t& enemigos);
	int throwGun(Player *player) override;
	bool ready() override;
	int actualGun() const;
};


class Guard: public Soldier {
	public:
	Guard(int& bullets);
	int shoot(Player *player, std::map<int, Player*>&) override;
	int throwGun(Player *player) override;
	bool ready() override;
	int actualGun() const;
};


class SS: public Soldier {
	private:
	bool gun;
	
	public:
	SS(int &balas);
	bool addGun();
	int shoot(Player *player, std::map<int, Player*>&) override;	
	int throwGun(Player *player) override;
	bool ready() override;
	int actualGun() const;
};


class Officer: public Soldier {
	private:
	bool gun;
	
	public:
	Officer(int &bullets);
	bool addGun();
	int shoot(Player *player, std::map<int, Player*>&) override;
	int throwGun(Player *player) override;
	bool ready() override;
	int actualGun() const;
};


class Mutant: public Soldier {
	private:
	bool gun;
	
	public:
	Mutant(int &bullets);
	bool addGun();
	int shoot(Player *player, std::map<int, Player*>&) override;	
	int throwGun(Player *player) override;
	bool ready() override;
	int actualGun() const;
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
