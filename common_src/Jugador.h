#ifndef __JUGADOR__
#define __JUGADOR__


#include "Posicionable.h"

#include "coordinates.h"
class Mapa;
#include "Mapa.h"
class Direccion;
#include "Direccion.h"

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
    explicit Jugador(Texture &texture_drawer,Coordinates posicion,Coordinates direction ,Mapa& mapa);

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
