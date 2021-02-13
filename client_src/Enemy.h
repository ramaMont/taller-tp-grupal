#ifndef __ENEMY__
#define __ENEMY__

#include <Posicionable.h>
#include <coordinates.h>
class Direccion;
#include <Direction.h>

class ClientMap;
#include "ClientMap.h"

class Character;
#include "Character.h"
#include "SpriteDrawer.h"
#include "EnemyType.h"

/* Es tanto un Movible como un sprite, dado que su 
metodo para dibujar es el mismo que el de los sprites*/
class Enemy : public Character, public SpriteDrawer{
private:
	Player &player;	
	bool is_moving;
	int moved_frames_continued;
	EnemyType* enemy_type;

public:
	explicit Enemy(Coordinates posicion,\
		Coordinates direction ,ClientMap& map, Player &player ,int id);

    //Pre:-
    // Le indico al rayo que colisionó con un enemigo y setea al 
    // enemigo como 'avistado' para que luego sea dibujado
    void colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle);

    //Pre:-
    // Cambio el tipo actual del enemigo
    void newEnemyType(int new_enemy_type);

    CharacterType getType()override;

    // Pre:-
    // Seteo que el jugador se está moviendo
	void moving();

    // Pre:-
    // Le indico al arma actual que fue disparada
	void shoot(SoundPlayer& soundPlayer, float distance);

    //Pre:-
    // Actualiza el actual frame del enemigo
	void updateFrame();

    //Pre:-
    // Llamo a su dibujador de texturas
	void callDrawer(int first_sigted_ray,int first_num_pixel,\
				 int last_sigted_ray,int last_num_pixel,float player_distance) override;

    //Pre:-
    // Libero la memoria del tipo de enemigo
	~Enemy();
};

#endif
