#ifndef __OBJETO__
#define __OBJETO__

#include "Posicionable.h"
#include "coordinates.h"
class Jugador;
#include "Jugador.h"

class Objeto: public Posicionable {
	public:
	Objeto(Coordinates coordenadas): Posicionable(coordenadas) { }
};


class Pared: public Objeto {
	public:
	Pared(Coordinates coordenadas): Objeto(coordenadas) { }
};


class ParedFalsa: public Pared {
	public:
	ParedFalsa(Coordinates coordenadas): Pared(coordenadas) { }
	void abrir(Jugador *jugador);
};


class Puerta: public Objeto {
	private:
	bool abierta = false;
	
	public:
	Puerta(Coordinates coordenadas): Objeto(coordenadas) { }
	virtual void abrir(Jugador *jugador);
	void abrirPuerta(Jugador *jugador);
	void cerrar();
};


class PuertaCerrada: public Puerta {
	private:
	bool llave = false;
	
	public:
	PuertaCerrada(Coordinates coordenadas): Puerta(coordenadas) { }
	void abrir(Jugador *jugador) override;
};


class Barril: public Objeto {
	public:
	Barril(Coordinates coordenadas): Objeto(coordenadas) { }
};


class Mesa: public Objeto {
	public:
	Mesa(Coordinates coordenadas): Objeto(coordenadas) { }
};


class Silla: public Objeto {
	public:
	Silla(Coordinates coordenadas): Objeto(coordenadas) { }
};

#endif
