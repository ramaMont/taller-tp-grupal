#ifndef __ARMA_H__
#define __ARMA_H__

#include "Posicionable.h"
class Jugador;
#include "Item.h"
class Mapa;


#define N_CUCHILLO 0
#define N_PISTOLA 1
#define N_AMETRALLADORA 2
#define N_CANION 3
#define N_LANZACOHETES 4


class Arma {
	public:
	virtual void disparar(Jugador* jugador) = 0;
};


class Cuchillo: public Arma {
	private:
	bool atacar(Mapa &mapa, Jugador* jugador, Coordinates &direccion);
	
	public:
	Cuchillo() { }
	void disparar(Jugador* jugador) override;
};


class Pistola: public Arma {
	private:
	float precision;
	
	public:
	void setParametros(const float precision);
	void disparar(Jugador* jugador) override;
};


class Ametralladora: public Arma, public Item {
	private:
	float precision;
	
	public:
	explicit Ametralladora(Coordinates p): Item(p) { }
	void setParametros(const float precision);
	void disparar(Jugador* jugador) override;
	bool usar(Jugador* jugador) override;
};


class CanionDeCadena: public Arma, public Item {
	private:
	float precision;
	
	public:
	explicit CanionDeCadena(Coordinates p): Item(p) { }
	void setParametros(const float precision);
	void disparar(Jugador* jugador) override;
	bool usar(Jugador* jugador) override;
};


class Lanzacohetes: public Arma, public Item {
	public:
	explicit Lanzacohetes(Coordinates p): Item(p) { }
	void disparar(Jugador* jugador) override;
	bool usar(Jugador* jugador) override;
};


class Cohete: public Posicionable{
	private:
	Coordinates direccion;
	
	public:
	Cohete(Coordinates posicion, Coordinates dir);
	void disparar(Jugador* jugador);
	void avanzar(Mapa& mapa);
	void explotar(Jugador* jugador, Mapa& mapa);
};
	

#endif
