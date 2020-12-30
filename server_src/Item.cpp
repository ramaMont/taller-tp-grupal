#include "Item.h"
#include "Player.h"
#include "ParamReaderServer.h"


Item::Item(Coordinates p): Posicionable(p) { 
	atravesable(true);
}

bool Comida::usar(Player* jugador){
	return jugador->agregarVida((int)configs[CONFIG::puntos_comida]);
}

bool KitMedico::usar(Player* jugador){
	return jugador->agregarVida((int)configs[CONFIG::puntos_kit]);
}

bool Sangre::usar(Player* jugador){
	if (jugador->estaPorMorir()){
		jugador->agregarVida(1);
		return true;
	}
	return false;
}


Balas::Balas(Coordinates p): Item(p){
	this->cantidad = (int)configs[CONFIG::cantidad_balas];
}

Balas::Balas(Coordinates p, int cant): Item(p){
	this->cantidad = cant;
}

bool Balas::usar(Player* jugador){
	return jugador->agregarBalas(this->cantidad);
}


bool Llave::usar(Player* jugador){
	return jugador->agregarLlave();
}


Tesoro::Tesoro(int puntuacion, Coordinates p): Item(p), puntuacion(puntuacion){
}

bool Tesoro::usar(Player* jugador){
	jugador->agregarPuntos(this->puntuacion);
	return true;
}

Cruz::Cruz(Coordinates p): Tesoro((int)configs[CONFIG::puntos_cruz], p){
}

Copa::Copa(Coordinates p): Tesoro((int)configs[CONFIG::puntos_copa], p){
}

Cofre::Cofre(Coordinates p): Tesoro((int)configs[CONFIG::puntos_cofre], p){
}

Corona::Corona(Coordinates p): Tesoro((int)configs[CONFIG::puntos_corona], p){
}

