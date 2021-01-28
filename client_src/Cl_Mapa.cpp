#include "Cl_Mapa.h"
#include "Character.h"
#include "Jugador.h"
#include "Enemy.h"
#include <iostream>
#include <utility>
#include <cmath>
#include <vector>

// Codigo de errores en int (despues cambiar a excepciones)
// -1 lugar no encontrado
// -2 lugar ocupado

Cl_Mapa::Cl_Mapa(): alto(0), ancho(0){
}

Cl_Mapa::Cl_Mapa(int alto, int ancho):alto(alto), ancho(ancho),mapaJuego(ancho,
        std::vector<Posicionable*>(alto)){
    for (int i=0; i<ancho; i++){
        for (int j=0; j<alto; j++){
            mapaJuego[i][j]=nullptr;
        }
    }
}

void Cl_Mapa::agregarJugador(Character* jugador){
    player = jugador;
	//mapaJuego[floor(jugador->getPosicion().x)]
    //    [floor(jugador->getPosicion().y)]=jugador;
}

void Cl_Mapa::agregarPosicionable(Posicionable* posicionable, 
        Coordinates posicion){
    if(mapaJuego[floor(posicion.x)][floor(posicion.y)]==nullptr){
        mapaJuego[floor(posicion.x)][floor(posicion.y)]=posicionable;
    }else{
        throw -2;//Quiero guardar algo donde ya hay otra cosa
    }
}

void Cl_Mapa::relocate(Character* jugador, Coordinates posicion){
        if(mapaJuego[floor(posicion.x)][floor(posicion.y)]==nullptr){
            mapaJuego[floor(posicion.x)][floor(posicion.y)]=jugador;
        }else{
            mapaJuego[floor(posicion.x)][floor(posicion.y)]->add(jugador);
            //throw -2;//Quiero guardar algo donde ya hay otra cosa
        }
}


void Cl_Mapa::sacarPosicionable(Coordinates posicion){
    if(mapaJuego[floor(posicion.x)][floor(posicion.y)]!=nullptr){
        try{
            mapaJuego[floor(posicion.x)][floor(posicion.y)]->remove();
        }catch (int e){
            mapaJuego[floor(posicion.x)][floor(posicion.y)]=nullptr;
        }
    }
}

Posicionable* Cl_Mapa::obtenerPosicionableEn(Coordinates posicion){
	return mapaJuego[floor(posicion.x)][floor(posicion.y)];
}

void Cl_Mapa::moveme(Character* jugador, const Coordinates& posicion){
	
    if (posicion.x > alto || posicion.y > ancho)
        throw -1;
    if (posicion.x < 0 || posicion.y < 0)
        throw -1;
    Coordinates posJugador = jugador->get_position();
    if (jugador->get_position() == posicion){
        return;
    }
    try {
        relocate(jugador,posicion);
        sacarPosicionable(posJugador);
    } catch(int e){
        throw;
    }
}

void Cl_Mapa::resize(int ancho, int alto){
    this->ancho = ancho;
    this->alto = alto;
    mapaJuego.resize(alto, std::vector<Posicionable*>(ancho));
}

//Problema: intento borrar tambien la posicion donde almaceno el jugador..."solucion": lo saco manualmente...
Cl_Mapa::~Cl_Mapa(){
    sacarPosicionable(player->get_position());
    for(int i=0; i<alto; i++){
         for(int j=0; j<ancho; j++){
            if(mapaJuego[i][j]!=nullptr){
                delete mapaJuego[i][j];
            }
        }   
    }
}
