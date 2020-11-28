#include <math.h>
#include <string>
#include <vector>

#include "ray_casting.h"

#include "window.h"

#include "camera.h"
#include "Jugador.h"
#include "coordinates.h"

#include "ray.h"


Raycasting::Raycasting(Jugador &a_player,Mapa &a_map,const Window &window)
    : player(a_player), map(a_map),renderer(window.getRenderer()) 
    {
    h=480;
    n_rays = 160;
}


void Raycasting::draw(float distance_player_plane,float pos_x){
	int lineHeight = (int)(h / distance_player_plane);
	int drawStart = -lineHeight / 2 + h / 2;
	if(drawStart < 0)drawStart = 0;
	int drawEnd = lineHeight / 2 + h / 2;
	if(drawEnd >= h)drawEnd = h - 1;

    if(player.get_direction().y>0){
	    for(int i=0; i<640/(2*n_rays);i++){
			SDL_RenderDrawLine(renderer,i+ 640*(pos_x+n_rays)/(2*n_rays), drawStart,i+ 640*(pos_x+n_rays)/(2*n_rays), drawEnd);
		}
	}else{//Si estoy aca empiezo x la derecha
	    for(int i=0; i<640/(2*n_rays);i++){
			SDL_RenderDrawLine(renderer,i+ 640 - 640*(pos_x+n_rays)/(2*n_rays), drawStart,i+640- 640*(pos_x+n_rays)/(2*n_rays), drawEnd);
		}		
	}
}


void Raycasting::calculate_ray_casting(){
    //Ademas del raycasting, estas funciones sirven 
    // para hacer el techo oscuro, y el piso claro con un triangulo (despues pasar a otra clase)
    //SDL_SetRenderDrawColor(renderer, 0x6E, 0x6E, 0x6E, 0 );
    //SDL_RenderFillRect( renderer, &roof );
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    /* Futuro mutex acá (en un thread proceso 
    botones, actualizo la posicion, etc y en otro 
    corro esto, que recibe la posicion, por esta mismma razon
    recibe una copia, así una vez recibida, pueden correr
    ambos en simultaneo)*/
    Coordinates player_coordinates = player.get_coordinates();
    Coordinates player_direction = player.get_direction();
    Camera camera(player_coordinates,player_direction);
	for(int i=-n_rays; i<=n_rays; i++){
		Coordinates ray_direction = camera.calculate_ray_direction(i,n_rays);
		float ray_angle = atan(std::abs((float)i/(float)n_rays));
		Ray ray(ray_angle, ray_direction,player_coordinates,player_direction,map);
		float wall_distance = ray.calculate_ray_distance();
		draw(wall_distance,i);
	}
}