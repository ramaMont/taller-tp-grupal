#ifndef __ITEM__
#define __ITEM__

#include "Posicionable.h"
class Jugador;


class Item: public Posicionable {
	public:
	explicit Item(Posicion p): Posicionable(p) { }
	virtual bool usar(Jugador* jugador) = 0;
};


class Comida: public Item {
	public:
	explicit Comida(Posicion p): Item(p) { }
	bool usar(Jugador* jugador) override;
};

class KitMedico: public Item {
	public:
	explicit KitMedico(Posicion p): Item(p) { }
	bool usar(Jugador* jugador) override;
};

class Sangre: public Item {
	public:
	explicit Sangre(Posicion p): Item(p) { }
	bool usar(Jugador* jugador) override;
};


class Balas: public Item {
	int cantidad;
	public:
	explicit Balas(Posicion p);
	explicit Balas(Posicion p, int cant);
	bool usar(Jugador* jugador) override;
	//~Balas() { }
};


class Llave: public Item {
	public:
	explicit Llave(Posicion p): Item(p) { }
	bool usar(Jugador* jugador) override;
	//virtual ~Llave();
};


class Tesoro: public Item {
	private:
	int puntuacion;
	public:
	explicit Tesoro(int puntuacion, Posicion p);
	bool usar(Jugador* jugador) override;
};

class Cruz: public Tesoro {
	public:
	explicit Cruz(Posicion p);
};

class Copa: public Tesoro {
	public:
	explicit Copa(Posicion p);
};

class Cofre: public Tesoro {
	public:
	explicit Cofre(Posicion p);
};

class Corona: public Tesoro {
	public:
	explicit Corona(Posicion p);
};


#endif
