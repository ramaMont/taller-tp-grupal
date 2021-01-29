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
class Direccion;
#include "Cl_Direccion.h"

class Character;
#include <Character.h>

class Gun_type;
#include "Gun_type.h"

class Player final : public Character{
private:
	int shot_frame;
	Gun_type* gun_type;
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

    void complete(Coordinates initial_position,Coordinates initial_direction,int player_id);

    // Cambio el arma actual del jugador
    void new_gun_type(int new_gun_type);

    // Inicializo la animacion de disparo o la actualizo en caso de que siga disparando
    void shoot();

    bool can_shoot();

    // Actualizo el frame del arma
    void update_shots();

    void resurrect() override;

    // Llamo a la funcion correspondiente para que dibuje el arma
    void draw();

    void updateHealth(int amount);

    void updateAmmo(int amount);

    void addPoints(int amount);

    ~Player();  
};

#endif
