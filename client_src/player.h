#ifndef PLAYER_H
#define PLAYER_H

#include "coordinates.h"

const float step_size = 0.1;
const float rotation_size = 0.05;

// Encargada del movimiento y la direccion del jugador
class Player{

private:
    Coordinates pos;
    Coordinates dir;

    // Mueve izquierda o derecha (relativo a su direccion)
    // Pre: -
    // SI MI DIRECCION EN EL EJE Y ES NEGATIVA SE ME INVIERTEN LAS DIRECCIONES, CORREGIR ESO
    void move_side(float inc);

    // Mueve arriba o abajo (relativo a su direccion)
    // Pre: -
    void move_front(float inc);

    // Rota al jugador
    // Pre: -
    void rotate_player(float inc);
public:
    Player(float x_pos, float y_pos, float x_dir, float y_dir);


    Coordinates get_coordinates();

    Coordinates get_direction();

    // Mueve adelante
    // Pre: -
    void move_forward();

    // Mueve atras
    // Pre: -    
    void move_backward();

    // Mueve izquierda
    // Pre: -
    void move_left();

    // Mueve derecha
    // Pre: -
    void move_right();

    // Rota izquierda
    // Pre: -
    void rotate_left();

    // Rota derecha
    // Pre: -
    void rotate_right();

};    

#endif
