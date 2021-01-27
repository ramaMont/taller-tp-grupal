#ifndef __JUGADOR__
#define __JUGADOR__

#include <thread>
#include <chrono>
#include <iostream>
#include <sys/time.h>

#include <Posicionable.h>

#include "coordinates.h"
class Cl_Mapa;
#include "Cl_Mapa.h"
class Direccion;
#include "Cl_Direccion.h"

class Movable;
#include <Movable.h>

class Gun_type;
#include "Gun_type.h"

class Jugador final : public Movable{
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
    explicit Jugador(Coordinates posicion,Coordinates direction ,Cl_Mapa& mapa, int id);

    explicit Jugador(Cl_Mapa& mapa);

    void complete(Coordinates initial_position,Coordinates initial_direction,int player_id);

    // Cambio el arma actual del jugador
    void new_gun_type(int new_gun_type);

    // Inicializo la animacion de disparo o la actualizo en caso de que siga disparando
    void shoot();

    bool can_shoot();

    // Actualizo el frame del arma
    void update_shots();

    void resurrect();

    // Llamo a la funcion correspondiente para que dibuje el arma
    void draw();

    void updateHealth(int amount);

    ~Jugador();  
};

#endif
