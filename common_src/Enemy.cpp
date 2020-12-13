#include "Enemy.h"

#include "Mapa.h"

static void draw_with_y_positive(Drawer &drawer, const std::vector<float> distances,int n_rays,int first_ray,int cant_rays,int num_texture,float player_distance  ){
		for(int i=0 ; i<cant_rays ; i++){
			int num_pixel = i*64/cant_rays;
			if((first_ray + i+ n_rays)>0 and (first_ray + i+ n_rays)<2*n_rays)
				if(distances[first_ray + i+ n_rays]>player_distance)
					drawer.draw_guard(first_ray + i,player_distance ,num_pixel,num_texture);
		}

}

static void draw_with_y_negative(Drawer &drawer, const std::vector<float> distances,int n_rays,int first_ray,int cant_rays,int num_texture,float player_distance  ){
		for(int i=0 ; i<cant_rays ; i++){
			int num_pixel =63 -  i*64/cant_rays;
			if((first_ray + i+ n_rays)>0 and (first_ray + i+ n_rays)<2*n_rays)
				if(distances[first_ray + i+ n_rays]>player_distance){
					drawer.draw_guard(first_ray + i,player_distance ,num_pixel,num_texture);
				}
		}

}

void Enemy::draw(Drawer &drawer, const std::vector<float> distances, int n_rays){
	printf("drawwwwww\n");
	printf("player_distance : %f\n",player_distance );
	int first_ray = center_ray - cant_rays/2;
	if(player.get_direction().y>0)
		draw_with_y_positive(drawer,distances,n_rays,first_ray,cant_rays,texture,player_distance);
	else
		draw_with_y_negative(drawer,distances,n_rays,first_ray,cant_rays,texture,player_distance);
}


void Enemy::mover_en_una_direccion(Coordinates nuevaPos){
    Coordinates movimiento_unidireccional;
    movimiento_unidireccional.x = nuevaPos.x;
    movimiento_unidireccional.y = this->posicion.y;

    try{
        mapa.moveEnemy(this, movimiento_unidireccional);
        this->posicion = movimiento_unidireccional;
    } catch(...){
    }

    movimiento_unidireccional.x = this->posicion.x;
    movimiento_unidireccional.y = nuevaPos.y;

    try{
        mapa.moveEnemy(this, movimiento_unidireccional);
        this->posicion = movimiento_unidireccional;
    } catch(...){
    }

}

void Enemy::mover(Coordinates nuevaPos){
    try{
        mapa.moveEnemy(this, nuevaPos);
        this->posicion = nuevaPos;
    } catch(...){
        mover_en_una_direccion(nuevaPos);
    }
}