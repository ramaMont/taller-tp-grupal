#include "Mapa.h"
#include <iostream>
#include <utility>
#include <cmath>
#include <vector>

// Codigo de errores en int (despues cambiar a excepciones)
// -1 lugar no encontrado
// -2 lugar ocupado

Mapa::Mapa(int alto, int ancho):alto(alto), ancho(ancho),mapaJuego(ancho,
        std::vector<Posicionable*>(alto)){
    for (int i=0; i<ancho; i++){
        for (int j=0; j<alto; j++){
            mapaJuego[i][j]=nullptr;
        }
    }
}

void Mapa::agregarJugador(Jugador* jugador){
	mapaJuego[floor(jugador->getPosicion().x)]
        [floor(jugador->getPosicion().y)]=jugador;
}

void Mapa::agregarPosicionable(Posicionable* posicionable, 
        Coordinates posicion){
	if(mapaJuego[floor(posicion.x)][floor(posicion.y)]==nullptr){
		mapaJuego[floor(posicion.x)][floor(posicion.y)]=posicionable;
	}else{
		throw -2;//Quiero guardar algo donde ya hay otra cosa
	}
}

void Mapa::sacarPosicionable(Coordinates posicion){
   mapaJuego[floor(posicion.x)][floor(posicion.y)]=nullptr;
}

Posicionable* Mapa::obtenerPosicionableEn(Coordinates posicion){
	return mapaJuego[floor(posicion.x)][floor(posicion.y)];
}

void Mapa::moveme(Jugador* jugador, const Coordinates& posicion){
    // for(int i=0; i<alto; i++){
    // 	for(int j=0; j<ancho; j++){
    // 		if(mapaJuego[i][j]!=0){
    // 			printf("P");
    // 		}else{
    // 			printf("_");
    // 		}
    // 	}
    // 	printf("\n");
    // }
    // printf("\n\n\n");
	
    if (posicion.x > ancho || posicion.y > alto)
        throw -1;
    if (posicion.x < 0 || posicion.y < 0)
        throw -1;
    Coordinates posJugador = jugador->getPosicion();
    if (jugador->getPosicion() == posicion){
        return;
    }
    try {
        agregarPosicionable(jugador, posicion);
        sacarPosicionable(posJugador);
    } catch(int e){
        throw;
    }
}

void Mapa::soltar(Posicionable* objeto){
}

Mapa::~Mapa(){
}
