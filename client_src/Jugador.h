#ifndef __JUGADOR__
#define __JUGADOR__


#include "Cl_Posicionable.h"

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
	int frames_since_shot;
	Gun_type* gun_type;
	bool shooting;	

public:
    explicit Jugador(Texture &texture, Coordinates posicion,Coordinates direction ,Cl_Mapa& mapa, int id);

    explicit Jugador(Texture &texture, Cl_Mapa& mapa);

    void complete(Coordinates initial_position,Coordinates initial_direction,int player_id);

    // Cambio el arma actual del jugador
    void new_gun_type(int new_gun_type);

    // Inicializo la animacion de disparo o la actualizo en caso de que siga disparando
    void shoot();

    // Actualizo el frame del arma
    void update_shots();

    // Llamo a la funcion correspondiente para que dibuje el arma
    void draw();

    ~Jugador();  
};

#endif
