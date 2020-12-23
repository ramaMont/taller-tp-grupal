#ifndef __ENEMY__
#define __ENEMY__

#include "Posicionable.h"

#include "coordinates.h"
class Mapa;
#include "Mapa.h"
class Direccion;
#include "Direccion.h"

class Movable;
#include <Movable.h>

#include "Sprite_drawer.h"

#include "Enemy_type.h"

// Es tanto un Movible como un sprite, dado que su metodo para dibujar es el mismo que el de los sprites
class Enemy : public Movable, public Sprite_drawer{
private:
	Jugador &player;	
	int num_texture;
	std::string id;
	int moved_frames_continued;
	Enemy_type* enemy_type;

public:
	explicit Enemy(Texture &texture_drawer,Coordinates posicion, int num_texture, Coordinates direction ,Mapa& mapa, Jugador &player ,std::string id);

	// En caso de colisionar con un enemigo durante el raycasting, le mando que aún no encontró una pared
    Intersected_object colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle);

    // Cambio el tipo actual del enemigo
    void new_enemy_type(int new_enemy_type);

    // Actualizo el frame del enemigo en caso de que se esté modviendo
	void moving();

	// Actualizo el frame del enemigo en caso de que esté quieto
	void still();

	// Dibujo al enemigo
	void draw(const std::vector<float> &distances, int n_rays);

	~Enemy();

};

#endif
