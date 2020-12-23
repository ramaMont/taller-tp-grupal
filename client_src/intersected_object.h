#ifndef __INTERSECTED_OBJECT__
#define __INTERSECTED_OBJECT__

class Posicionable;
#include <Posicionable.h>

class Texture;
class Wall;
//Datos necesarios para el gráfico de la pared con raycasting, incluida la misma pared colisionada
class Intersected_object{
private:
	int number_line_texture;//Fila de pixeles a graficar (eje x)
    float distance;
    Wall* object;
    bool wall_side_y; //Si el objeto está en el eje x, el valor es 1, si está en y, es 2 y más oscura

public:
	//Cargo las caracteristicas de la pared colisionada.
    explicit Intersected_object(float distance_player_plane,Wall* object ,float position, bool wall_side_y);

    //Llama al dibujar de la correspondiente pared con los datos necesarios
    void draw(int x_pixel);
    
};

#endif
