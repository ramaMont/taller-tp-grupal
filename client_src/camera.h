#ifndef CAMERA_H
#define CAMERA_H
#include <string>
#include <coordinates.h>
#include <math.h>

// "Camara" representativa que se solo en raycasting para calcular 
// la distancia de cada rayo
class Camera {
private:
	Coordinates coordinates_camera;
	//"Plano"(vector) perpendicular a la direccion del jugador
	Coordinates camera_plane; 
	Coordinates player_position;

public:
	Camera(const Coordinates &player_position, Coordinates &player_direction);

	// Calculo un rayo que partiendo del jugador, "choque" con un 
	// punto en el plano.
	Coordinates calculate_ray_direction(int i, int n_rays);
};

#endif
