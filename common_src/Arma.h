#ifndef __ARMA_H__
#define __ARMA_H__

#include "Posicionable.h"
class Jugador;
#include "Item.h"
class Mapa;
#include <set>


#define N_CUCHILLO 0
#define N_PISTOLA 1
#define N_AMETRALLADORA 2
#define N_CANION 3
#define N_LANZACOHETES 4

typedef std::set<std::pair<int, Jugador*>> angulos_enemigos_t;

class Arma {
	public:
	virtual void disparar(Jugador* jugador, angulos_enemigos_t& enemigos) {}
	virtual void disparar(Jugador* jugador, std::vector<Jugador*>& enemigos) {}
};


class Cuchillo: public Arma {
	public:
	Cuchillo() { }
	void disparar(Jugador* jugador, angulos_enemigos_t& enemigos) override;
};


class Pistola: public Arma {
	private:
	float precision;
	
	public:
	void setParametros(const float precision);
	void disparar(Jugador* jugador, angulos_enemigos_t& enemigos) override;
};


class Ametralladora: public Arma, public Item {
	private:
	float precision;
	
	public:
	explicit Ametralladora(Coordinates p): Item(p) { }
	void setParametros(const float precision);
	void disparar(Jugador* jugador, angulos_enemigos_t& enemigos) override;
	bool usar(Jugador* jugador) override;
};


class CanionDeCadena: public Arma, public Item {
	private:
	float precision;
	
	public:
	explicit CanionDeCadena(Coordinates p): Item(p) { }
	void setParametros(const float precision);
	void disparar(Jugador* jugador, angulos_enemigos_t& enemigos) override;
	bool usar(Jugador* jugador) override;
};


class Lanzacohetes: public Arma, public Item {
	public:
	explicit Lanzacohetes(Coordinates p): Item(p) { }
	void disparar(Jugador* jugador, std::vector<Jugador*>& enemigos) override;
	bool usar(Jugador* jugador) override;
};


class Cohete: public Posicionable{
	private:
	const Coordinates direccion;
	
	public:
	Cohete(Coordinates posicion, const Coordinates dir);
	void disparar(Jugador* jugador, std::vector<Jugador*>& enemigos);
	void avanzar(Mapa& mapa);
	void explotar(Jugador* jugador, std::vector<Jugador*>& enemigos);
};
	

#endif
