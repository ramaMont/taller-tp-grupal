#ifndef __ENEMY__
#define __ENEMY__

#include "Posicionable.h"

#include "coordinates.h"
class Cl_Mapa;
#include "Cl_Mapa.h"
class Direccion;
#include "Cl_Direccion.h"

class Character;
#include <Character.h>

#include "Sprite_drawer.h"

#include "Enemy_type.h"

// Es tanto un Movible como un sprite, dado que su metodo para dibujar es el mismo que el de los sprites
class Enemy : public Character, public Sprite_drawer{
private:
	Jugador &player;	
	bool is_moving;
	int moved_frames_continued;
	Enemy_type* enemy_type;

public:
	explicit Enemy(Coordinates posicion, Coordinates direction ,Cl_Mapa& mapa, Jugador &player ,int id);

	// En caso de colisionar con un enemigo durante el raycasting, le mando que aún no encontró una pared
    void colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle);

    // Cambio el tipo actual del enemigo
    void new_enemy_type(int new_enemy_type);

    // Actualizo el frame del enemigo en caso de que se esté modviendo
	void moving();

	void shoot();

	void update_frame();

	// Dibujo al enemigo
	void draw(const std::vector<float> &distances, int n_rays);

	~Enemy();

};

#endif
