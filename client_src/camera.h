#ifndef CAMERA_H
#define CAMERA_H

#include <coordinates.h>

#include <math.h>
#include <string>

// "Camara" representativa para calcular la distancia de cada rayo en raycasting
class Camera {
private:
	Coordinates coordinates_camera;
	Coordinates camera_plane; //vector perpendicular a la direccion del jugador
	const Coordinates player_position;

public:
	Camera(const Coordinates &player_position,const Coordinates &player_direction);

	// Calculo un rayo que partiendo del jugador, 
	// "choque" con un punto en el plano.
	Coordinates calculateRayDirection(int i, int n_rays);

	Coordinates getCameraPlane();
};

#endif
