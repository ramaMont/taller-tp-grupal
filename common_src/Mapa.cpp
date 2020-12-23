#include "Mapa.h"
#include <iostream>
#include <utility>
#include <cmath>
#include <vector>

// Codigo de errores en int (despues cambiar a excepciones)
// -1 lugar no encontrado
// -2 lugar ocupado

// Pongo esta funcion global horrible aca, para inicializar los mapas de 
// manera momentanea.
void initMap(Mapa& map){
    std::vector<std::vector<int>> a_map{
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    for (int i=0; i<24; i++){
        for (int j=0; j<24; j++){
            if (a_map[i][j]!=0){
                Coordinates position((float)i,(float)j);
                Posicionable* posicionable = new Posicionable(position);
                map.agregarPosicionable(posicionable,position);
            }
        }
    }
}


Mapa::Mapa(int map_id):
        alto(24),
        ancho(24),
        mapaJuego(ancho, std::vector<Posicionable*>(alto)){
    for (int i=0; i<ancho; i++){
        for (int j=0; j<alto; j++){
            mapaJuego[i][j]=nullptr;
        }
    }
    initMap(*this);
}

Mapa::Mapa(int alto, int ancho):alto(alto), ancho(ancho),mapaJuego(ancho,
        std::vector<Posicionable*>(alto)){
    for (int i=0; i<ancho; i++){
        for (int j=0; j<alto; j++){
            mapaJuego[i][j]=nullptr;
        }
    }
}

void Mapa::agregarPlayer(Player* jugador){
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

void Mapa::moveme(Player* jugador, const Coordinates& posicion){
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
    Coordinates posPlayer = jugador->getPosicion();
    if (jugador->getPosicion() == posicion){
        return;
    }
    try {
        agregarPosicionable(jugador, posicion);
        sacarPosicionable(posPlayer);
    } catch(int e){
        throw;
    }
}

Mapa::Mapa(Mapa&& other){
    this->alto = other.alto;
    this->ancho = other.ancho;
    this->mapaJuego.swap(other.mapaJuego);
}

Mapa& Mapa::operator=(Mapa&& other){
    if (this == &other){
        return *this;        // other is myself!
    }
    this->alto = other.alto;
    this->ancho = other.ancho;
    this->mapaJuego.swap(other.mapaJuego);
    return *this;
}

// Se encarga de limpiar los vectores con usuarios y jugadores.
Mapa::~Mapa(){
    if (!mapaJuego.empty()){
        for (int i = 0; i < alto; ++i){
            for (int j = 0; j < ancho; ++j){
                delete(mapaJuego[i][j]);
            }
        }
    }
}
