
#include <string>
#include "coordinates.h"
#include <math.h>

#include "camera.h"


Camera::Camera(const Coordinates &player_position,const Coordinates &player_direction):
	player_position(player_position)
	{
		float n = 1/sqrt(pow(player_direction.x,2) + pow(player_direction.y,2));
		coordinates_camera.x =player_position.x + n*player_direction.x;
		coordinates_camera.y =player_position.y + n*player_direction.y;

		camera_plane = player_direction.get_perpendicular_direction();
		if(player_direction.y<=0){
			camera_plane.y = -camera_plane.y;
			camera_plane.x = -camera_plane.x;
		}
		camera_plane.normalice_direction();
	}

	// Calculo un rayo que partiendo del jugador, "choque" con un punto en el plano.
Coordinates Camera::calculateRayDirection(int i, int n_rays){
	Coordinates ray; //Punto del "plano" de la camara por el cual tiene que pasar mi rayo
	ray.x = coordinates_camera.x + camera_plane.x*(float)i/(float)n_rays;
	ray.y = coordinates_camera.y + camera_plane.y*(float)i/(float)n_rays;
	Coordinates ray_direction; 
	ray_direction.x=ray.x-player_position.x;
	ray_direction.y=ray.y-player_position.y;
	return ray_direction;
}


Coordinates Camera::getCameraPlane(){
	return camera_plane;
}