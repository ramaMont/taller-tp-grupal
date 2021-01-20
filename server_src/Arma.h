#ifndef __ARMA_H__
#define __ARMA_H__

#include "Posicionable.h"
class Player;
#include "Item.h"
class Mapa;
#include <set>
#include <map>


#define N_CUCHILLO 0
#define N_PISTOLA 1
#define N_AMETRALLADORA 2
#define N_CANION 3
#define N_LANZACOHETES 4

typedef std::set<std::pair<int, Player*>> angulos_enemigos_t;

class Arma {
	public:
	virtual void disparar(Player* jugador, angulos_enemigos_t& enemigos) {}
	virtual void disparar(Player* jugador, std::map<int, Player*>& enemigos) {}
};


class Cuchillo: public Arma {
	public:
	Cuchillo() { }
	void disparar(Player* jugador, angulos_enemigos_t& enemigos) override;
};


class Pistola: public Arma {
	public:
	void disparar(Player* jugador, angulos_enemigos_t& enemigos) override;
};


class Ametralladora: public Arma, public Item {
	public:
	Ametralladora(): Item(Coordinates(0,0))  {}
	explicit Ametralladora(Coordinates p): Item(p) { }
	void disparar(Player* jugador, angulos_enemigos_t& enemigos) override;
	bool usar(Player* jugador) override;
};


class CanionDeCadena: public Arma, public Item {
	public:
	CanionDeCadena(): Item(Coordinates(0,0)) {}
	explicit CanionDeCadena(Coordinates p): Item(p) { }
	void disparar(Player* jugador, angulos_enemigos_t& enemigos) override;
	bool usar(Player* jugador) override;
};


class Lanzacohetes: public Arma, public Item {
	public:
	Lanzacohetes(): Item(Coordinates(0,0))  {}
	explicit Lanzacohetes(Coordinates p): Item(p) { }
	void disparar(Player* jugador, std::map<int, Player*>& enemigos) override;
	bool usar(Player* jugador) override;
};

#endif
