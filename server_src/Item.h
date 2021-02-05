#ifndef __ITEM__
#define __ITEM__

#include "Posicionable.h"
class Player;


class Item: public Posicionable {
	public:
	explicit Item(Coordinates p);
	virtual bool use(Player* player) = 0;
	Coordinates& getPosition(); //
	void setPosition(Coordinates& position);
};


class Food: public Item {
	public:
	explicit Food(Coordinates p): Item(p) { }
	bool use(Player* player) override;
};

class Medicine: public Item {
	public:
	explicit Medicine(Coordinates p): Item(p) { }
	bool use(Player* player) override;
};

class Blood: public Item {
	public:
	explicit Blood(Coordinates p): Item(p) { }
	bool use(Player* player) override;
};


class Bullets: public Item {
	int cantidad;
	public:
	explicit Bullets(Coordinates p);
	explicit Bullets(Coordinates p, int cant);
	bool use(Player* player) override;
};


class Key: public Item {
	public:
	explicit Key(Coordinates p): Item(p) { }
	bool use(Player* player) override;
};


class MachineGun: public Item {
	public:
	explicit MachineGun(Coordinates p): Item(p) { }
	bool use(Player* player) override;
};


class FireCanon: public Item {
	public:
	explicit FireCanon(Coordinates p): Item(p) { }
	bool use(Player* player) override;
};


class RocketLauncher: public Item {
	public:
	explicit RocketLauncher(Coordinates p): Item(p) { }
	bool use(Player* player) override;
};


class Treasure: public Item {
	private:
	int score;
    
	public:
	explicit Treasure(int score, Coordinates p);
	bool use(Player* player) override;
};

class Cross: public Tesoro {
	public:
	explicit Cross(Coordinates p);
};

class Trophie: public Tesoro {
	public:
	explicit Trophie(Coordinates p);
};

class Chest: public Tesoro {
	public:
	explicit Chest(Coordinates p);
};

class Crown: public Tesoro {
	public:
	explicit Crown(Coordinates p);
};


#endif
