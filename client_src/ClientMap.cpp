#include "ClientMap.h"
#include "Movable.h"
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

ClientMap::ClientMap(): alto(0), ancho(0){
}

ClientMap::ClientMap(int alto, int ancho):alto(alto), ancho(ancho),mapGame(ancho,
        std::vector<Posicionable*>(alto)){
    for (int i=0; i<ancho; i++){
        for (int j=0; j<alto; j++){
            mapGame[i][j]=nullptr;
        }
    }
}

void ClientMap::addPlayer(Character* _player){
    this->player = _player;
}

void ClientMap::addPositionable(Posicionable* positionable, 
        Coordinates position){
    if(mapGame[floor(position.x)][floor(position.y)]==nullptr){
        mapGame[floor(position.x)][floor(position.y)]=positionable;
    }else{
        throw -2;//Quiero guardar algo donde ya hay otra cosa
    }
}

void ClientMap::addMovable(Movable* _player, Coordinates position){
        if(mapGame[floor(position.x)][floor(position.y)]==nullptr){
            mapGame[floor(position.x)][floor(position.y)]=_player;
        }else{
            mapGame[floor(position.x)][floor(position.y)]->add(_player);
            //throw -2;//Quiero guardar algo donde ya hay otra cosa
        }
}

void ClientMap::removePositionable(Coordinates position){
    mapGame[floor(position.x)][floor(position.y)]=nullptr;
}


void ClientMap::removeMovable(Coordinates position){
    if(mapGame[floor(position.x)][floor(position.y)]!=nullptr){
        try{
            mapGame[floor(position.x)][floor(position.y)]->remove();
        }catch (int e){
            removePositionable(position);
        }
    }
}

void ClientMap::removeAllPositionables(Coordinates position){
    mapGame[floor(position.x)][floor(position.y)]=nullptr;
}

void ClientMap::removeSpriteWithCharacter(Coordinates position, Movable* character){
    mapGame[floor(position.x)][floor(position.y)]=character;
}

Posicionable* ClientMap::getPositionableIn(Coordinates position){
	return mapGame[floor(position.x)][floor(position.y)];
}

void ClientMap::moveme(Movable* _player, const Coordinates& position){
	
    if (position.x > alto || position.y > ancho)
        throw -1;
    if (position.x < 0 || position.y < 0)
        throw -1;
    Coordinates posPlayer = _player->get_position();
    if (_player->get_position() == position){
        return;
    }
    try {
        addMovable(_player,position);
        removeMovable(posPlayer);
    } catch(int e){
        throw;
    }
}

void ClientMap::resize(int ancho, int alto){
    this->ancho = ancho;
    this->alto = alto;
    mapGame.resize(alto, std::vector<Posicionable*>(ancho));
}

ClientMap::~ClientMap(){
}
