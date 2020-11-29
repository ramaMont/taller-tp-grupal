#include "Arma.h"

#include "Jugador.h"

void Cuchillo::atacar(Jugador* jugador){
}


void Pistola::atacar(Jugador* jugador){
}


void Ametralladora::atacar(Jugador* jugador){
}

bool Ametralladora::usar(Jugador* jugador){
	return jugador->agregarArma(this);
}


void CanionDeCadena::atacar(Jugador* jugador){
}

bool CanionDeCadena::usar(Jugador* jugador){
	return jugador->agregarArma(this);
}


void Lanzacohetes::atacar(Jugador* jugador){
}

bool Lanzacohetes::usar(Jugador* jugador){
	return jugador->agregarArma(this);
}
