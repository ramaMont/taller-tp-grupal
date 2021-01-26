#ifndef __OBJETO__
#define __OBJETO__

#include "Posicionable.h"
#include "coordinates.h"
class Player;
#include "Player.h"
class ThGameModelServer;
class Mapa;
#include <map>

class Objeto: public Posicionable {
	public:
	Objeto(Coordinates coordenadas): Posicionable(coordenadas) { }
    Coordinates& getCoordinates();
};


class ParedFalsa: public Objeto {
	public:
	ParedFalsa(Coordinates coordenadas);
	bool abrir(Player *jugador);
};


class Puerta: public Objeto {
	private:
	bool abierta = false;
	bool has_event;
	std::atomic<bool> reopen;
	
	public:
	Puerta(Coordinates coordenadas);
	virtual bool abrir(Player *jugador);
	bool abrirPuerta(Player *jugador);
	std::atomic<bool>& getReopen();
	void cerrar();
};


class PuertaCerrada: public Puerta {
	private:
	bool llave = false;
	
	public:
	PuertaCerrada(Coordinates coordenadas): Puerta(coordenadas) { }
	bool abrir(Player *jugador) override;
};


class Rocket: public Objeto{
    private:
    Coordinates position;
    Coordinates direction;
    Player* player;
    std::map<int, Player*>& enemies;
    Mapa& map;
    std::atomic<bool> exploded;

    public:
    Rocket(Coordinates position, Coordinates dir,Player* player,
        std::map<int, Player*>& enemies, ThGameModelServer& game_model);
    void move(ThGameModelServer& game_model);
    void explode();
    bool hasExploded();
    bool colisionaConObjeto(const Coordinates& inicio, const Coordinates& fin);
    ~Rocket();
};

#endif
