#ifndef __PLAYER__
#define __PLAYER__

#include <thread>
#include <chrono>

#include <Posicionable.h>
#include <coordinates.h>
class Direction;
#include <Direction.h>

class ClientMap;
#include "ClientMap.h"
class Character;
#include "Character.h"
class GunType;
#include "GunType.h"
#include "SoundPlayer.h"

class Player final : public Character{
private:
    const int max_health;
    const int init_bullets;
	int shot_frame;
	GunType* gun_type;
	bool shooting;	
    int frames_per_shot;
    int current_shoot_frame;
    unsigned int score;
    int lives;
    int health;
    int ammo;
    bool has_key_1;
    bool has_key_2;

public:
    explicit Player(ClientMap& map);

    Player(const Player&) = delete;
    Player(Player&& other) = delete;
    Player& operator=(const Player&) = delete;
    Player& operator=(Player&& other);

    //Pre:-
    // Completo los datos iniciales del jugador
    void complete(Coordinates initial_position,\
    		Coordinates initial_direction,int player_id);

    // Cambio el arma actual del jugador
    void newGunType(int new_gun_type);

    int getFramesPerShot();

    bool gunAllowsContinuousShooting();

    /* Pre:-
    Inicializo la animacion de disparo o la 
    actualizo en caso de que siga disparando*/
    void shoot(SoundPlayer& soundPlayer, float distance);

    //Pre:-
    // Devuelve si el jugador puede disparar    
    bool canShoot();

    // Actualizo el frame del arma
    void updateShots();

    /*Pre:-
    Se agrega a si mismo al mapa, vuelve a setear su
     posicion y direccion a las iniciales, y resetea su vida al maximo*/
    void resurrect() override;

    // Llamo a la funcion correspondiente para que dibuje el arma
    void draw();

    CharacterType getType() override;

    //Pre:-
    // Actualiza su salud
    void updateHealth(int amount);

    //Pre:-
    // Actualiza la cantidad de balas
    void updateAmmo(int amount);

    //Pre:-
    // Actualiza la cantidad de puntos totales
    void addPoints(int amount);

    //Pre:-
    // Actualiza la cantidad de llaves
    void updateKeys(int amount);

    //Pre:-
    // Libero la memoria del arma
    ~Player();  
};

#endif
