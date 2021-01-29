#include "ClMap.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include <utility>
#include <cmath>
#include <vector>

// Codigo de errores en int (despues cambiar a excepciones)
// -1 lugar no encontrado
// -2 lugar ocupado

ClMap::ClMap(): alto(0), ancho(0){
}

ClMap::ClMap(int alto, int ancho):alto(alto), ancho(ancho),mapGame(ancho,
        std::vector<Posicionable*>(alto)){
    for (int i=0; i<ancho; i++){
        for (int j=0; j<alto; j++){
            mapGame[i][j]=nullptr;
        }
    }
}

void ClMap::addPlayer(Character* _player){
    this->player = _player;
	//mapGame[floor(jugador->getPosicion().x)]
    //    [floor(jugador->getPosicion().y)]=jugador;
}

void ClMap::addPositionable(Posicionable* positionable, 
        Coordinates position){
    if(mapGame[floor(position.x)][floor(position.y)]==nullptr){
        mapGame[floor(position.x)][floor(position.y)]=positionable;
    }else{
        throw -2;//Quiero guardar algo donde ya hay otra cosa
    }
}

void ClMap::relocate(Character* _player, Coordinates position){
        if(mapGame[floor(position.x)][floor(position.y)]==nullptr){
            mapGame[floor(position.x)][floor(position.y)]=_player;
        }else{
            mapGame[floor(position.x)][floor(position.y)]->add(_player);
            //throw -2;//Quiero guardar algo donde ya hay otra cosa
        }
}


void ClMap::removePositionable(Coordinates position){
    if(mapGame[floor(position.x)][floor(position.y)]!=nullptr){
        try{
            mapGame[floor(position.x)][floor(position.y)]->remove();
        }catch (int e){
            mapGame[floor(position.x)][floor(position.y)]=nullptr;
        }
    }
}

void ClMap::removeSpriteWithCharacter(Coordinates position, Character* character){
    mapGame[floor(position.x)][floor(position.y)]=character;
}

Posicionable* ClMap::getPositionableIn(Coordinates position){
	return mapGame[floor(position.x)][floor(position.y)];
}

void ClMap::moveme(Character* _player, const Coordinates& position){
	
    if (position.x > alto || position.y > ancho)
        throw -1;
    if (position.x < 0 || position.y < 0)
        throw -1;
    Coordinates posPlayer = _player->get_position();
    if (_player->get_position() == position){
        return;
    }
    try {
        relocate(_player,position);
        removePositionable(posPlayer);
    } catch(int e){
        throw;
    }
}

void ClMap::resize(int ancho, int alto){
    this->ancho = ancho;
    this->alto = alto;
    mapGame.resize(alto, std::vector<Posicionable*>(ancho));
}

//Problema: intento borrar tambien la position donde almaceno el jugador..."solucion": lo saco manualmente...
ClMap::~ClMap(){
    removePositionable(player->get_position());//Ojo si el jugador esta sobre un sprite y borro todo así
    for(int i=0; i<alto; i++){
         for(int j=0; j<ancho; j++){
            if(mapGame[i][j]!=nullptr){
                delete mapGame[i][j];
            }
        }   
    }
}
