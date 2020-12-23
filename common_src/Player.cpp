#include "Player.h"
#include <stdio.h>

Player::Player(Coordinates position,Coordinates direction ,Mapa& mapa):
    Posicionable(position),direction(direction), mapa(mapa), player_id(0){
    mapa.agregarPlayer(this);
}

Player::Player(Coordinates position,Coordinates direction ,Mapa& mapa, int id):
        Posicionable(position),direction(direction), mapa(mapa), player_id(id){
    mapa.agregarPlayer(this);
}

void Player::mover(Direccion* direccion){
    Coordinates nuevaPos = direccion->mover(this,direction);
    try{
        mapa.moveme(this, nuevaPos);
        this->posicion = nuevaPos;
    } catch(...){
    }
}

Coordinates Player::get_coordinates(){
    return posicion;
}

Coordinates Player::get_direction(){
    return direction;
}

void Player::set_direction(Coordinates direction){
    this->direction = direction;
}

int Player::getId(){
    return player_id;
}

Player::~Player(){
}
