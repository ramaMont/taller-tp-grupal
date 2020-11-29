#ifndef __ARMA_H__
#define __ARMA_H__

#include "Posicionable.h"
class Jugador;
#include "Item.h"


#define N_CUCHILLO 0
#define N_PISTOLA 1
#define N_AMETRALLADORA 2
#define N_CANION 3
#define N_LANZACOHETES 4


class Arma {
	public:
	virtual void atacar(Jugador* jugador) = 0;
};


class Cuchillo: public Arma {
	public:
	Cuchillo() { }
	void atacar(Jugador* jugador) override;
};


class Pistola: public Arma {
	public:
	void atacar(Jugador* jugador) override;
};


class Ametralladora: public Arma, public Item {
	public:
	explicit Ametralladora(Posicion p): Item(p) { }
	void atacar(Jugador* jugador) override;
	bool usar(Jugador* jugador) override;
};


class CanionDeCadena: public Arma, public Item {
	public:
	explicit CanionDeCadena(Posicion p): Item(p) { }
	void atacar(Jugador* jugador) override;
	bool usar(Jugador* jugador) override;
};


class Lanzacohetes: public Arma, public Item {
	public:
	explicit Lanzacohetes(Posicion p): Item(p) { }
	void atacar(Jugador* jugador) override;
	bool usar(Jugador* jugador) override;
};
	

#endif
