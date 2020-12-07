#include "Item.h"

#include "Jugador.h"

#define PUNTOS_COMIDA 10
#define PUNTOS_KIT 20
#define CANT_BALAS 5
#define PUNTOS_CRUZ 10
#define PUNTOS_COPA 50
#define PUNTOS_COFRE 100
#define PUNTOS_CORONA 200


Item::Item(Coordinates p): Posicionable(p) { 
	puedoPasar(true);
}

bool Comida::usar(Jugador* jugador){
	return jugador->agregarVida(PUNTOS_COMIDA);
}

bool KitMedico::usar(Jugador* jugador){
	return jugador->agregarVida(PUNTOS_KIT);
}

bool Sangre::usar(Jugador* jugador){
	if (jugador->estaPorMorir()){
		jugador->agregarVida(1);
		return true;
	}
	return false;
}


Balas::Balas(Coordinates p): Item(p){
	this->cantidad = CANT_BALAS;
}

Balas::Balas(Coordinates p, int cant): Item(p){
	this->cantidad = cant;
}

bool Balas::usar(Jugador* jugador){
	return jugador->agregarBalas(this->cantidad);
}


bool Llave::usar(Jugador* jugador){
	return jugador->agregarLlave();
}


Tesoro::Tesoro(int puntuacion, Coordinates p): Item(p), puntuacion(puntuacion){
}

bool Tesoro::usar(Jugador* jugador){
	jugador->agregarPuntos(this->puntuacion);
	return true;
}

Cruz::Cruz(Coordinates p): Tesoro(PUNTOS_CRUZ, p){
}

Copa::Copa(Coordinates p): Tesoro(PUNTOS_COPA, p){
}

Cofre::Cofre(Coordinates p): Tesoro(PUNTOS_COFRE, p){
}

Corona::Corona(Coordinates p): Tesoro(PUNTOS_CORONA, p){
}

