#include "Mapa.h"
#include <iostream>
#include <utility>
#include <cmath>
#include <typeinfo>
#include "Objeto.h"
#include "Item.h"


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
        mapaJuego(ancho, std::vector<std::vector<Posicionable*>>(alto)){
   /* for (int i=0; i<ancho; i++){
        for (int j=0; j<alto; j++){
            mapaJuego[i][j]=nullptr;
        }
    }*/
    initMap(*this);
}

Mapa::Mapa(int alto, int ancho):alto(alto), ancho(ancho),mapaJuego(ancho,
        std::vector<std::vector<Posicionable*>>(alto)){
    /*for (int i=0; i<ancho; i++){
        for (int j=0; j<alto; j++){
            mapaJuego[i][j]=nullptr;
        }
    }*/
}

void Mapa::agregarPlayer(Player* jugador){
	const Coordinates& posicion = jugador->getPosicion();
	mapaJuego[floor(posicion.x)][floor(posicion.y)].push_back(jugador);
}

void Mapa::agregarPosicionable(Posicionable* posicionable, 
        Coordinates posicion){
	if (floor(posicion.x) < 0 || floor(posicion.x) >= ancho ||
	    floor(posicion.y) < 0 || floor(posicion.y) >= alto) return;
	if(mapaJuego[floor(posicion.x)][floor(posicion.y)].empty()){
		mapaJuego[floor(posicion.x)][floor(posicion.y)].push_back(posicionable);
	}else{
		std::vector<Posicionable*>& vec = 
		    mapaJuego[floor(posicion.x)][floor(posicion.y)];
		if (vec.back()->atravesable()){
			vec.push_back(posicionable);
		}else{
			throw -2;//Quiero guardar algo donde ya hay otra cosa
		}
	}
}

void Mapa::sacarPosicionable(Coordinates posicion){
    if (!mapaJuego[floor(posicion.x)][floor(posicion.y)].empty())
	    mapaJuego[floor(posicion.x)][floor(posicion.y)].pop_back();
}

Posicionable* Mapa::obtenerPosicionableEn(Coordinates posicion) const{
	if (floor(posicion.x) < 0 || floor(posicion.x) >= ancho ||
	    floor(posicion.y) < 0 || floor(posicion.y) >= alto) return nullptr;
	if (mapaJuego[floor(posicion.x)][floor(posicion.y)].empty())
		return nullptr;
	return mapaJuego[floor(posicion.x)][floor(posicion.y)].back();
}

void Mapa::moveme(Player* jugador, const Coordinates& posicion){
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

void Mapa::soltar(Posicionable* objeto, const Coordinates& posicion){
	if (floor(posicion.x) < 0 || floor(posicion.x) >= ancho ||
	    floor(posicion.y) < 0 || floor(posicion.y) >= alto) return;
	mapaJuego[floor(posicion.x)][floor(posicion.y)].push_back(objeto);
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
	    mapaJuego[floor(x)][floor(y)].back()->atravesable());
}

bool Mapa::hayPuertaEn(float x, float y) const{
	if (floor(x) < 0 || floor(x) >= ancho ||
	    floor(y) < 0 || floor(y) >= alto ||
	    mapaJuego[floor(x)][floor(y)].empty()) return false;
	return typeid(*mapaJuego[floor(x)][floor(y)].back()) == typeid(Puerta);
}

int Mapa::getAlto() const{
	return this->alto;
}

int Mapa::getAncho() const{
	return this->ancho;
}

// Se encarga de limpiar los vectores con usuarios y jugadores.
Mapa::~Mapa(){
    if (!mapaJuego.empty()){
        for (int i = 0; i < alto; ++i){
            for (int j = 0; j < ancho; ++j){
                for (Posicionable* p: mapaJuego[i][j]){
                    delete(p);
                }
            }
        }
    }
}
