#ifndef __SOLDIER__H_
#define __SOLDIER__H_

#include <coordinates.h>
#include <BlockingQueue.h>
#include <Protocol.h>

#include <set>
#include <vector>
#include <atomic>
#include <map>
#include <utility>

class ServerMap;
class Player;

enum GunNumber{
    KNIFE = 0,
    GUN,
    MACHINE_GUN,
    CANON_GUN,
    ROCKET_GUN
};


class Soldier {
protected:
	int &bullets;
    bool gun;
   
    // Obtiene los enemigos que estan en su rango de disparo y los guarda
    // en el parametro 'players'
    void getCloserEnemies(std::map<int, Player*>& enemies,
        Player* player, std::set<std::pair<int, Player*>>& players,
        float precision);
       
    // Intenta dispar a sus enemigos, lo logra si no los intercepta ningun
	// objeto
    void tryShoot(Player* player, std::set<std::pair<int, Player*>>& enemies,
		float precision);
    
    // Retorna true en caso de que haya algun objeto entre start y end en el 
	// mapa
    bool crashes(ServerMap& map, const Coordinates& start, 
		const Coordinates& end);
    
    // El jugador ataca al enemigo, el danio depende de los parametros 
    void atack(Player* player, Player* enemy, float precision, int angle);
    
    // Retorna true si el jugador puede atacar al enemigo
    bool fireBullet(Player* player, float precision, int angle, Player* enemy);
    
    
public:
    explicit Soldier(int &bullets): bullets(bullets), gun(true) { }
    
    // El soldado intenta disparar a sus enemigos
	virtual int shoot(Player *player, std::map<int, Player*>& enemies) = 0;
    
    // El soldado deja su arma en la posicion del mapa
    // En caso de que pueda retorna la textura del arma, sino retorna 0
	virtual int throwGun(ServerMap& map, const Coordinates& position) = 0;
    
    // Retorna true en caso de que el soldado este listo para disparar
	virtual bool ready() = 0;
    
    // Devuelve el numero correspondiente a su arma
	virtual int gunNumber() const = 0;
	
    // Retorna true si el soldado no tenia arma y la agrega
    bool addGun();

	virtual ~Soldier() {}
};



class Dog: public Soldier {
public:
	explicit Dog(int& n);
	int shoot(Player *player, std::map<int, Player*>&) override;
    
    // El perro ataca a algun enemigo
	void bite(Player* player, std::set<std::pair<int, Player*>>& enemies);
    
	int throwGun(ServerMap& map, const Coordinates& position) override;
	bool ready() override;
	int gunNumber() const;
};


class Guard: public Soldier {
public:
	explicit Guard(int& bullets);
	int shoot(Player *player, std::map<int, Player*>&) override;
	int throwGun(ServerMap& map, const Coordinates& position) override;
	bool ready() override;
	int gunNumber() const;
};


class SS: public Soldier {
public:
	explicit SS(int &bullets);
	int shoot(Player *player, std::map<int, Player*>&) override;	
	int throwGun(ServerMap& map, const Coordinates& position) override;
	bool ready() override;
	int gunNumber() const;
};


class Officer: public Soldier {
public:
	explicit Officer(int &bullets);
	int shoot(Player *player, std::map<int, Player*>&) override;
	int throwGun(ServerMap& map, const Coordinates& position) override;
	bool ready() override;
	int gunNumber() const;
};


class Mutant: public Soldier {
public:
	explicit Mutant(int &bullets);
	int shoot(Player *player, std::map<int, Player*>&) override;	
	int throwGun(ServerMap& map, const Coordinates& position) override;
	bool ready() override;
	int gunNumber() const;
};


class SoldierState {
private:
	Player *player;
	Soldier *soldier;
	Dog dog;
	Guard guard;
	SS ss;
	Officer officer;
	Mutant mutant;
	Soldier *last_soldier;
	std::atomic<int> actual_gun;
    BlockingQueue<Protocol>& game_model_queue;
	
public:
	explicit SoldierState(Player *player, int& bullets,
        BlockingQueue<Protocol>& game_model_queue);
    
    // Retorna el numero de arma actual
	int actualGun();
    
    // Agrega al soldado correspondiente su arma
    // Retorna true en caso de agregar esa arma, false si ya la tenia
	bool addGun(int gun_number);
    
    // Cambia de soldado dependiendo de su arma
	void switchGun(int gun_number);
    
    // El soldado actual deja su arma en la posicion del mapa
	int throwGun(const Coordinates& position);
    
    // El soldado actual intenta disparar
    // REtorna 0 en caso de lograrlo, 1 si el soldado es el mutante
	int shoot(std::map<int, Player*>& enemies);
    
    // Notifica que se recargaron balas
	void rechargeBullets();
};

#endif
