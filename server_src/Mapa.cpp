#include "Mapa.h"
#include <iostream>
#include <utility>
#include <cmath>
#include <vector>
#include <typeinfo>
#include "Objeto.h"

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
		if (pila.top()->atravesable()){
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

Posicionable* Mapa::obtenerPosicionableEn(Coordinates posicion) const{
	if (floor(posicion.x) < 0 || floor(posicion.x) >= ancho ||
	    floor(posicion.y) < 0 || floor(posicion.y) >= alto) return nullptr;
	if (mapaJuego[floor(posicion.x)][floor(posicion.y)].empty())
		return nullptr;
	return mapaJuego[floor(posicion.x)][floor(posicion.y)].top();
}

void Mapa::moveme(Jugador* jugador, const Coordinates& posicion){
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
	if (floor(posicion.x) < 0 || floor(posicion.x) >= ancho ||
	    floor(posicion.y) < 0 || floor(posicion.y) >= alto) return;
	mapaJuego[floor(posicion.x)][floor(posicion.y)].push(objeto);
}

void Mapa::soltar(Posicionable objeto){
	soltar(&objeto, objeto.getPosicion());
}

bool Mapa::hayObstaculoEn(const Coordinates& posicion) const{
	return hayObstaculoEn(posicion.x, posicion.y);
}

bool Mapa::hayObstaculoEn(float x, float y) const{
	if (floor(x) < 0 || floor(x) >= ancho ||
	    floor(y) < 0 || floor(y) >= alto) return true;
	return !(mapaJuego[floor(x)][floor(y)].empty() ||
	    mapaJuego[floor(x)][floor(y)].top()->atravesable());
}

bool Mapa::hayPuertaEn(float x, float y) const{
	if (floor(x) < 0 || floor(x) >= ancho ||
	    floor(y) < 0 || floor(y) >= alto ||
	    mapaJuego[floor(x)][floor(y)].empty()) return false;
	return typeid(*mapaJuego[floor(x)][floor(y)].top()) == typeid(Puerta);
}

int Mapa::getAlto() const{
	return this->alto;
}

int Mapa::getAncho() const{
	return this->ancho;
}

Mapa::~Mapa(){
}
