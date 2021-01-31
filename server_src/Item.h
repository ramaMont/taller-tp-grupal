#ifndef __ITEM__
#define __ITEM__

#include "Posicionable.h"
class Player;


class Item: public Posicionable {
	public:
	explicit Item(Coordinates p);
	virtual bool usar(Player* jugador) = 0;
	Coordinates& getPosition();
	void setPosition(Coordinates& position);
};


class Comida: public Item {
	public:
	explicit Comida(Coordinates p): Item(p) { }
	bool usar(Player* jugador) override;
};

class KitMedico: public Item {
	public:
	explicit KitMedico(Coordinates p): Item(p) { }
	bool usar(Player* jugador) override;
};

class Sangre: public Item {
	public:
	explicit Sangre(Coordinates p): Item(p) { }
	bool usar(Player* jugador) override;
};


class Balas: public Item {
	int cantidad;
	public:
	explicit Balas(Coordinates p);
	explicit Balas(Coordinates p, int cant);
	bool usar(Player* jugador) override;
};


class Llave: public Item {
	public:
	explicit Llave(Coordinates p): Item(p) { }
	bool usar(Player* jugador) override;
};


class Tesoro: public Item {
	private:
	int puntuacion;
	public:
	explicit Tesoro(int puntuacion, Coordinates p);
	bool usar(Player* jugador) override;
};

class Cruz: public Tesoro {
	public:
	explicit Cruz(Coordinates p);
};

class Copa: public Tesoro {
	public:
	explicit Copa(Coordinates p);
};

class Cofre: public Tesoro {
	public:
	explicit Cofre(Coordinates p);
};

class Corona: public Tesoro {
	public:
	explicit Corona(Coordinates p);
};


#endif
