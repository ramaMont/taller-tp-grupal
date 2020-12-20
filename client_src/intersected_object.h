#ifndef __INTERSECTED_OBJECT__
#define __INTERSECTED_OBJECT__

class Posicionable;
#include <Posicionable.h>

//Datos necesarios para el gráfico del objeto colisionado con raycasting
class Intersected_object{
private:
	int number_line_texture;//Fila de pixeles a graficar (eje x)
    float distance;
    Posicionable* object;//A éste despues le tengo que hacer get_texture_number para saber q textura usar
    bool wall_side_y; //Si el objeto está en el eje x, el valor es 1, si está en y, es 2 y más oscura

public:
	//Cargo las caracteristicas del objeto colisionado (proximamente agregear n° textura)
    explicit Intersected_object(float distance_player_plane,Posicionable* object ,float position, bool wall_side_y);

    int get_texture();
    
    float get_distance_player_plane();

    int get_number_line_texture();

    bool get_side_wall_colided();

    
};

#endif
