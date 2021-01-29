#ifndef __ENEMY__
#define __ENEMY__

#include "Posicionable.h"

#include "coordinates.h"
class ClMap;
#include "ClMap.h"
class Direccion;
#include "Cl_Direction.h"

class Character;
#include <Character.h>

#include "SpriteDrawer.h"

#include "EnemyType.h"

// Es tanto un Movible como un sprite, dado que su metodo para dibujar es el mismo que el de los sprites
class Enemy : public Character, public SpriteDrawer{
private:
	Player &player;	
	bool is_moving;
	int moved_frames_continued;
	EnemyType* enemy_type;

public:
	explicit Enemy(Coordinates posicion, Coordinates direction ,ClMap& map, Player &player ,int id);

	// En caso de colisionar con un enemigo durante el raycasting, le mando que aún no encontró una pared
    void colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle);

    // Cambio el tipo actual del enemigo
    void newEnemyType(int new_enemy_type);

    // Actualizo el frame del enemigo en caso de que se esté modviendo
	void moving();

	void shoot();

	void updateFrame();

	// Dibujo al enemigo
	void draw(const std::vector<float> &distances, int n_rays);

	~Enemy();

};

#endif
