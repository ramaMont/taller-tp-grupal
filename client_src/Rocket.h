#ifndef __ROCKET__
#define __ROCKET__

#include "Posicionable.h"

#include "coordinates.h"
class ClMap;
#include "ClMap.h"
class Direccion;
#include "Cl_Direction.h"

class Character;
#include <Character.h>

#include "texture.h"
#include "SpriteDrawer.h"


// Es tanto un Movible como un sprite, dado que su metodo para dibujar es el mismo que el de los sprites
class Rocket : public Character, public SpriteDrawer{
private:
	Player &player;	
	bool is_moving;
	int moved_frames_continued;

public:
	explicit Rocket(Coordinates posicion, Coordinates direction ,ClMap& map, Player &player ,int id);

    //Pre:-
    // Le indico al rayo que colisionó con un enemigo y setea al 
    // enemigo como 'avistado' para que luego sea dibujado
    void colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle);

    //Pre:-
    // Cambio el tipo actual del enemigo
    void newRocketType(int new_enemy_type);

    void changePosition(Coordinates position);

    //Pre:-
    // Actualiza el actual frame del enemigo
	void updateFrame();

    CharacterType getType() override;

    //Pre:-
    // Llamo a su dibujador de texturas
	void callDrawer(int first_sigted_ray,int first_num_pixel,int last_sigted_ray,int last_num_pixel,float player_distance) override;

    //Pre:-
    // Libero la memoria del tipo de enemigo
	~Rocket();

};

#endif