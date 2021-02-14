#ifndef __ROCKET__
#define __ROCKET__

#include <Posicionable.h>
#include <coordinates.h>
class Direccion;
#include <Direction.h>

class ClientMap;
#include "ClientMap.h"
class Character;
#include "Character.h"
#include "texture.h"
#include "SpriteDrawer.h"

/* Es tanto un Movible como un sprite, dado que su metodo
 para dibujar es el mismo que el de los sprites*/
class Rocket : public Movable, public SpriteDrawer{
private:

public:
	explicit Rocket(Coordinates posicion,Coordinates direction,\
					ClientMap& map, Player &player);

    //Pre:-
    // Le indico al rayo que colisionó con un enemigo y setea al 
    // enemigo como 'avistado' para que luego sea dibujado
    void colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle);

    void move();

    //Pre:-
    // Llamo a su dibujador de texturas
	void callDrawer(int first_sigted_ray,int first_num_pixel,\
				int last_sigted_ray,int last_num_pixel,\
						float player_distance) override;

    //Pre:-
    // Libero la memoria del tipo de enemigo
	~Rocket();
};

#endif
