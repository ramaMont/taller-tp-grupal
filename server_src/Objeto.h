#ifndef __OBJETO__
#define __OBJETO__

#include "Posicionable.h"
#include "coordinates.h"
class Player;
#include "Player.h"

class Objeto: public Posicionable {
	public:
	Objeto(Coordinates coordenadas): Posicionable(coordenadas) { }
};


class ParedFalsa: public Objeto {
	public:
	ParedFalsa(Coordinates coordenadas): Objeto(coordenadas) { }
	void abrir(Player *jugador);
};


class Puerta: public Objeto {
	private:
	bool abierta = false;
	
	public:
	Puerta(Coordinates coordenadas): Objeto(coordenadas) { }
	virtual void abrir(Player *jugador);
	void abrirPuerta(Player *jugador);
	void cerrar();
};


class PuertaCerrada: public Puerta {
	private:
	bool llave = false;
	
	public:
	PuertaCerrada(Coordinates coordenadas): Puerta(coordenadas) { }
	void abrir(Player *jugador) override;
};


#endif
