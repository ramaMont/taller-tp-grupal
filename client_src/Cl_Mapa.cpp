#include "Cl_Mapa.h"
#include "Movable.h"
#include "Jugador.h"
#include "Enemy.h"
#include <iostream>
#include <utility>
#include <cmath>
#include <vector>

// Codigo de errores en int (despues cambiar a excepciones)
// -1 lugar no encontrado
// -2 lugar ocupado

Cl_Mapa::Cl_Mapa(int alto, int ancho):alto(alto), ancho(ancho),mapaJuego(ancho,
        std::vector<Posicionable*>(alto)){
    for (int i=0; i<ancho; i++){
        for (int j=0; j<alto; j++){
            mapaJuego[i][j]=nullptr;
        }
    }
}

void Cl_Mapa::agregarJugador(Movable* jugador){
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

void Cl_Mapa::relocate(Movable* jugador, Coordinates posicion){
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
            printf("remuevoo\n");
            mapaJuego[floor(posicion.x)][floor(posicion.y)]=nullptr;
        }
    }
}

Posicionable* Cl_Mapa::obtenerPosicionableEn(Coordinates posicion){
	return mapaJuego[floor(posicion.x)][floor(posicion.y)];
}

void Cl_Mapa::moveme(Movable* jugador, const Coordinates& posicion){
	
    if (posicion.x > ancho || posicion.y > alto)
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


void Cl_Mapa::delete_element(Coordinates position_to_remove){

}

//Problema: intento borrar tambien la posicion donde almaceno el jugador..."solucion": lo saco manualmente...
Cl_Mapa::~Cl_Mapa(){
    sacarPosicionable(player->get_position());
    for(int i=0; i<ancho; i++){
         for(int j=0; j<alto; j++){
            if(mapaJuego[i][j]!=nullptr){
                delete mapaJuego[i][j];
            }
        }   
    }
}
