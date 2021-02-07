#ifndef __SPRITE_DRAWER__
#define __SPRITE_DRAWER__

#include <iostream>
#include <vector>

#include <math.h>

class Raycasting;
#include "rayCasting.h"

class Posicionable;
#include <Posicionable.h>

#include <coordinates.h>

// Obtiene la informacion necesaria para dibujar sprites, tanto sprites comunes como enemigos
class SpriteDrawer{
protected:
	Posicionable* posicionable;
	Player &player;
	bool located;
	float player_distance;
	double relative_angle_to_player;
	double lowest_ray_distance;
	int center_ray;
	int cant_rays;


public:
    explicit SpriteDrawer(Posicionable *posicionable, Player &player);

    void draw(const std::vector<float> &distances, int n_rays);

    virtual void callDrawer(int first_sigted_ray,int first_num_pixel,int last_sigted_ray,int last_num_pixel,float player_distance){}

    // Calcula su angulo relativo respecto a la direccion del jugador
    void setRelativeAngleToPlayer();

    // Obtiene el rayo de raycasting mas cercano a su posicion
	void updateDistanceToClosestRay(int i,int n_rays);

	// Calcula la distancia al plano del jugador
	void setDistance(int half_pixels,Coordinates camera_plane);

	// En caso de haber colisionado con un rayo, seteo el sprite como 'avistado'
	void spottedSprite();

	// True si el sprite fue visto, false en caso contrario
	bool isSpotted();

	// Desactiva el 'avistado' del frame anterior
	void disableSpotted();

	float getDistancePlayerPlane() const;

};

#endif
