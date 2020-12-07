#include "Mapa.h"
#include <iostream>
#include <utility>
#include <cmath>
#include <vector>
#include <typeinfo>

// Codigo de errores en int (despues cambiar a excepciones)
// -1 lugar no encontrado
// -2 lugar ocupado

Mapa::Mapa(int alto, int ancho):alto(alto), ancho(ancho),mapaJuego(ancho,
        std::vector<std::stack<Posicionable*>>(alto)){
    /*for (int i=0; i<ancho; i++){
        for (int j=0; j<alto; j++){
            mapaJuego[i][j]=nullptr;
        }
    }*/
}

void Mapa::agregarJugador(Jugador* jugador){
	const Coordinates& posicion = jugador->getPosicion();
	mapaJuego[floor(posicion.x)][floor(posicion.y)].push(jugador);
}

void Mapa::agregarPosicionable(Posicionable* posicionable, 
        Coordinates posicion){
	if (floor(posicion.x) < 0 || floor(posicion.x) >= ancho ||
	    floor(posicion.y) < 0 || floor(posicion.y) >= alto) return;
	if(mapaJuego[floor(posicion.x)][floor(posicion.y)].empty()){
		mapaJuego[floor(posicion.x)][floor(posicion.y)].push(posicionable);
	}else{
		std::stack<Posicionable*>& pila = 
		    mapaJuego[floor(posicion.x)][floor(posicion.y)];
		if (pila.top()->puedoPasar()){
			pila.push(posicionable);
		}else{
			throw -2;//Quiero guardar algo donde ya hay otra cosa
		}
	}
}

void Mapa::sacarPosicionable(Coordinates posicion){
    if (!mapaJuego[floor(posicion.x)][floor(posicion.y)].empty())
	    mapaJuego[floor(posicion.x)][floor(posicion.y)].pop();
}

Posicionable* Mapa::obtenerPosicionableEn(Coordinates posicion){
	if (floor(posicion.x) < 0 || floor(posicion.x) >= ancho ||
	    floor(posicion.y) < 0 || floor(posicion.y) >= alto) return nullptr;
	if (mapaJuego[floor(posicion.x)][floor(posicion.y)].empty())
		return nullptr;
	return mapaJuego[floor(posicion.x)][floor(posicion.y)].top();
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
	
    if (floor(posicion.x) >= ancho || floor(posicion.y) >= alto)
        throw -1;
    if (floor(posicion.x) < 0 || floor(posicion.y) < 0)
        throw -1;
    Coordinates posJugador = jugador->getPosicion();
    if (jugador->getPosicion() == posicion){
        return;
    }
    try {
		Posicionable* posicionable = obtenerPosicionableEn(posicion);
		if (posicionable && typeid(*posicionable) == typeid(Item) &&
			static_cast<Item*>(posicionable)->usar(jugador))
			sacarPosicionable(posicion);
        agregarPosicionable(jugador, posicion);
        sacarPosicionable(posJugador);
    } catch(int e){
        throw;
    }
}

void Mapa::soltar(Posicionable* objeto, const Coordinates& posicion){
	for (int p_x = posicion.x - 1; p_x < posicion.x + 1; p_x ++){
		for (int p_y = posicion.y - 1; p_y < posicion.y + 1; p_y ++){
			if (0 <= p_x && p_x < ancho && 0 <= p_y && p_y < alto){
				try {
					agregarPosicionable(objeto, Coordinates(p_x, p_y));
					break;
				} catch (...){
				}
			}
		}
	}
}

void Mapa::soltar(Posicionable objeto){
	soltar(&objeto, objeto.getPosicion());
}

Mapa::~Mapa(){
}
