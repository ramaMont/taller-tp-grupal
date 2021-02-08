#ifndef __DOOR__
#define __DOOR__

#include <string>
#include <Movable.h>
#include "Posicionable.h"
class Ray;

const int CANT_FRAMES_ANIMATION = 20;
const int TEXTURE_LENGTH = 64;

enum State { opening, open, closed};


class Door : public Posicionable{
private:
	int current_frame;
	State state;
	Movable* character;

public:
    explicit Door(Coordinates posicion);

    //Pre:-
    // Almacena a un personaje mientras este se encuentra en el casillero de la puerta
    void add(Movable* character) override;

    //Pre:-
    // Remueve al personaje una vez que este salga de su casillero
    void remove() override;

    //Pre:-
    // Le indica al movible que fue avistado
    void spottedMovable();

    //Pre:-
    // Le indica al rayo que colisionó con una puerta
	void colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle);

    //Pre:-
    // Setea su estado(abriendo, abierto, o cerrado)
	void setState(State new_state);

    //Pre:-
    // Actualiza el actual frame de la puerta
	void updateFrame(); 

    //Pre:-
    // Devuelve el maximo pixel que puede ser dibujado de la puerta según el frame en el que se encuentra
	int getLimitWall();

    //Pre:-
    // Llama a su respectivo dibujador de texturas
	void draw(int ray, float distance, int number_line_texture,bool wall_side_y);

};

#endif
