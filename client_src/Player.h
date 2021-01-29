#ifndef __PLAYER__
#define __PLAYER__

#include <thread>
#include <chrono>
#include <iostream>
#include <sys/time.h>

#include <Posicionable.h>

#include "coordinates.h"
class ClMap;
#include "ClMap.h"
class Direction;
#include "Cl_Direction.h"

class Character;
#include <Character.h>

class GunType;
#include "GunType.h"

class Player final : public Character{
private:
	int shot_frame;
	GunType* gun_type;
	bool shooting;	
    unsigned int score;
    time_t fire_rate;
    time_t time_shot_start;
    int lives;
    int health;
    int ammo;

public:
    explicit Player(Coordinates posicion,Coordinates direction ,ClMap& map, int id);

    explicit Player(ClMap& map);

    //Pre:-
    // Completo los datos iniciales del jugador
    void complete(Coordinates initial_position,Coordinates initial_direction,int player_id);

    // Cambio el arma actual del jugador
    void newGunType(int new_gun_type);

    // Inicializo la animacion de disparo o la actualizo en caso de que siga disparando
    void shoot();

    //Pre:-
    // Devuelve si el jugador puede disparar    
    bool canShoot();

    // Actualizo el frame del arma
    void updateShots();

    //Pre:-
    // Se agrega a si mismo al mapa, vuelve a setear su posicion y direccion a las iniciales, y resetea su vida al maximo
    void resurrect() override;

    // Llamo a la funcion correspondiente para que dibuje el arma
    void draw();

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
    // Libero la memoria del arma
    ~Player();  
};

#endif
