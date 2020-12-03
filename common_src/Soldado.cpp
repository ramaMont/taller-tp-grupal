#include "Soldado.h"

#include "Mapa.h"

#include <unistd.h>

#define BALAS_AMETRALLADORA 5
#define TIEMPO_AMETRALLADORA 3000000
#define BALAS_LANZACOHETES 5
#define TIEMPO_CANION 1000000


EstadoSoldado::EstadoSoldado(Jugador *jugador, int &balas): jugador(jugador),
    perro(Perro(balas)), guardia(Guardia(balas)), ss(SS(balas)),
    oficial(Oficial(balas)), mutante(Mutante(balas)){
	this->soldado = &perro;
}

bool EstadoSoldado::agregarArma(Arma* arma){
	if (static_cast<Ametralladora*>(arma)){
		return this->ss.agregarArma(static_cast<Ametralladora*>(arma));
	}
	if (static_cast<CanionDeCadena*>(arma)){
		return this->oficial.agregarArma(static_cast<CanionDeCadena*>(arma));
	}
	if (static_cast<Lanzacohetes*>(arma)){
		return this->mutante.agregarArma(static_cast<Lanzacohetes*>(arma));
	}
	return false;
}

void EstadoSoldado::cambiarArma(int numero_arma){
	switch (numero_arma){
		case N_CUCHILLO:
			this->soldado = &this->perro;
		case N_PISTOLA:
			if (this->guardia.estaListo())
				this->soldado = &this->guardia;
		case N_AMETRALLADORA:
			if (this->ss.estaListo())
				this->soldado = &this->ss;
		case N_CANION:
			if (this->oficial.estaListo())
				this->soldado = &this->oficial;
		case N_LANZACOHETES:
			if (this->mutante.estaListo())
				this->soldado = &this->mutante;
	}
}


void EstadoSoldado::soltarArma(){
	this->soldado->soltarArma(this->jugador);
}

void EstadoSoldado::disparar(Jugador *jugador){
	this->soldado->disparar(jugador);
	if (!this->soldado->estaListo())
		this->soldado = &this->perro;
}


// Perro

Perro::Perro(int& n): Soldado(n){
}

void Perro::disparar(Jugador *jugador){
	this->cuchillo.disparar(jugador);
}

void Perro::soltarArma(Jugador *jugador){
}

bool Perro::estaListo(){
	return true;
}


// Guardia

Guardia::Guardia(int& balas): Soldado(balas){
}

void Guardia::disparar(Jugador *jugador){
	this->pistola.disparar(jugador);
	this->balas --;
}

void Guardia::soltarArma(Jugador *jugador){
}

bool Guardia::estaListo(){
	return this->balas > 0;
}


// SS

SS::SS(int &balas): Soldado(balas){
}

bool SS::agregarArma(Ametralladora *ametr){
	if (this->ametralladora != nullptr)
		return false;
	this->ametralladora = ametr;
	return true;
}

void SS::disparar(Jugador *jugador){
	for (int i = 0; (i < BALAS_AMETRALLADORA) && (this->balas > 0); i ++){
		this->ametralladora->disparar(jugador);
		this->balas --;
		usleep(TIEMPO_AMETRALLADORA);
	}
}

void SS::soltarArma(Jugador *jugador){
	Mapa &mapa = jugador->getMapa();
	mapa.soltar(this->ametralladora, jugador->get_coordinates());
	this->ametralladora = nullptr;
}

bool SS::estaListo(){
	return this->balas > 0 && this->ametralladora != nullptr;
}


// Oficial

Oficial::Oficial(int &balas): Soldado(balas){
}

bool Oficial::agregarArma(CanionDeCadena *canion){
	if (this->canion != nullptr)
		return false;
	this->canion = canion;
	return true;
}
	
void Oficial::disparar(Jugador *jugador){
	for (int i = 0; (i < 1/*tiempo presionado*/) && (this->balas > 0); i ++){
		this->canion->disparar(jugador);
		this->balas --;
		usleep(TIEMPO_CANION);
	}	
}

void Oficial::soltarArma(Jugador *jugador){
	Mapa &mapa = jugador->getMapa();
	mapa.soltar(this->canion, jugador->get_coordinates());
	this->canion = nullptr;
}

bool Oficial::estaListo(){
	return this->balas > 0 && this->canion != nullptr;
}


// Mutante

Mutante::Mutante(int &balas): Soldado(balas){
}

bool Mutante::agregarArma(Lanzacohetes *lanzacohetes){
	if (this->lanzacohetes != nullptr)
		return false;
	this->lanzacohetes = lanzacohetes;
	return true;	
}

void Mutante::disparar(Jugador *jugador){
	this->lanzacohetes->disparar(jugador);
	this->balas -= BALAS_LANZACOHETES;
}

void Mutante::soltarArma(Jugador *jugador){
	Mapa &mapa = jugador->getMapa();
	mapa.soltar(this->lanzacohetes, jugador->get_coordinates());
	this->lanzacohetes = nullptr;
}

bool Mutante::estaListo(){
	return this->balas > BALAS_LANZACOHETES && this->lanzacohetes != nullptr;
}

