#ifndef __OBJECT__
#define __OBJECT__

#include <Posicionable.h>
#include "coordinates.h"
class Player;
#include "Player.h"
class ThGameModelServer;
class ServerMap;
#include <map>
#define ROCKET_STEP 0.25

class Object: public Posicionable {
	public:
	explicit Object(Coordinates coordinates): Posicionable(coordinates) { }
};


class Passage: public Object {
	public:
	explicit Passage(Coordinates coordinates);
    
    // Retorna true si el jugador puede abrir el pasadizo, sino false
	bool open(Player *player);
};


class Door: public Object {
	private:
	bool has_event; 
	std::atomic<bool> reopen;
	
	public:
	explicit Door(Coordinates coordinates);
    
    // Retorna true si el jugador puede abir la puerta
	virtual bool open(Player *player);
    
    // Retorna true si el jugador puede abrir la puerta
	bool openDoor(Player *player);
    
    // Retorna true en caso de que un jugador haya vuelto a abrir la puerta
	std::atomic<bool>& getReopen();
    
    // Abre la puerta, permite a los jugadores pasarla
	void letPass();
    
    // Cierra la puerta
	void close();
};


class KeyDoor: public Door {
	private:
	bool opened = false;
	
	public:
	explicit KeyDoor(Coordinates coordinates): Door(coordinates) { }
    
    // Retorna true si el jugador puede abir la puerta
	bool open(Player *player) override;
};


class Rocket: public Object{
    private:
    Coordinates direction;
    Player* player;
    std::map<int, Player*>& enemies;
    ServerMap& map;
    std::atomic<bool> exploded;

    public:
    explicit Rocket(Coordinates position, Coordinates dir,Player* player,
        std::map<int, Player*>& enemies, ThGameModelServer& game_model);
        
    // Mueve el cohete hacia adelante
    void move(ThGameModelServer& game_model);
    
    // Hace explotar el cohete
    void explode();
    
    // Retorna true en caso de que haya explotado el cohete
    bool hasExploded();
    
    // Retorna true si hay un objeto entre las posiciones start y end del mapa
    bool crashes(const Coordinates& start, const Coordinates& end);
    
    // Retorna su direccion
    Coordinates getDirection();
    ~Rocket();
};

#endif
