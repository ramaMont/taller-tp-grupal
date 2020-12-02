#include "Arma.h"

#include "Jugador.h"
#include <cstdlib>
#include <ctime>

#define PASO 1
#define ROTACION_45 0.125
#define MAXIMO_DANIO 10

#define MAXIMO_RANDOM 100
#define PORCENTAJE 100
#define RANGO_DISPARO 90
#define MITAD_RANGO_DISPARO 45
#define RANGO_COMPLETO 360


bool Cuchillo::atacar(Mapa &mapa, Jugador *jugador, Coordinates &direccion){
	Coordinates posicion = jugador->get_coordinates();
	posicion.increment_on_direction(direccion, PASO);
	Posicionable* objeto = mapa.obtenerPosicionableEn(posicion);
	if (!static_cast<Jugador*>(objeto))
		return false;

	Jugador *j = static_cast<Jugador*>(objeto);
	srand (time(0));
	int danio = rand() % MAXIMO_DANIO + 1;
	bool murio = j->recibirDanio(danio);
	if (murio)
		jugador->agregarEnemigoMuerto();
	return true;
}

void Cuchillo::disparar(Jugador* jugador){
	Mapa &mapa = jugador->getMapa();
	Coordinates direccion = jugador->get_direction();
	if (atacar(mapa, jugador, direccion))
		return;
	direccion.rotate(ROTACION_45);
	if (atacar(mapa, jugador, direccion))
		return;
	direccion.rotate(-ROTACION_45);	
	direccion.rotate(-ROTACION_45);
	atacar(mapa, jugador, direccion);
}


// Arma

bool atacar(Mapa &mapa, Jugador *jugador, Coordinates &direccion,
            int distancia, float precision){
	Coordinates posicion = jugador->get_coordinates();
	posicion.increment_on_direction(direccion, PASO);
	Posicionable* objeto = mapa.obtenerPosicionableEn(posicion);
	if (!static_cast<Jugador*>(objeto)) /* && no colisiona con objeto */{
		return atacar(mapa, jugador, direccion, distancia++, precision);
	}
    
	Jugador *j = static_cast<Jugador*>(objeto);
	srand (time(0));
	float danio_distancia = 1 / distancia;
	int danio = (rand() % MAXIMO_DANIO + 1) * danio_distancia;
	bool murio = j->recibirDanio(danio);
	if (murio)
		jugador->agregarEnemigoMuerto();
	return true;
}


void dispararBala(Jugador* jugador, float precision){
	srand (time(0));
	int n_rand = rand() % MAXIMO_RANDOM;
	if ((n_rand / PORCENTAJE) > precision)
		return;
    Coordinates dir = jugador->get_direction();
    atacar(jugador->getMapa(), jugador, dir, 0, precision);	
}


// Pistola

void Pistola::setParametros(const float precision){
	this->precision = precision;
}

void Pistola::disparar(Jugador* jugador){
	dispararBala(jugador, this->precision);
}


// Ametralladora

void Ametralladora::setParametros(const float precision){
	this->precision = precision;
}

void Ametralladora::disparar(Jugador* jugador){
	dispararBala(jugador, this->precision);
}

bool Ametralladora::usar(Jugador* jugador){
	return jugador->agregarArma(this);
}


// Canion de Cadena

void CanionDeCadena::setParametros(const float precision){
	this->precision = precision;
}

void CanionDeCadena::disparar(Jugador* jugador){
	dispararBala(jugador, this->precision);
}

bool CanionDeCadena::usar(Jugador* jugador){
	return jugador->agregarArma(this);
}


// Lanzacohetes

void Lanzacohetes::disparar(Jugador* jugador){
	Coordinates posicion = jugador->get_coordinates();
	Coordinates dir = jugador->get_direction();
	posicion.increment_on_direction(dir, 1);
	Cohete cohete(posicion, dir);
	cohete.disparar(jugador);
}

bool Lanzacohetes::usar(Jugador* jugador){
	return jugador->agregarArma(this);
}


// Cohete

Cohete::Cohete(Coordinates posicion, Coordinates dir): 
    Posicionable(posicion), direccion(dir) { 
}

void Cohete::disparar(Jugador* jugador){
	Mapa& mapa = jugador->getMapa();
	mapa.agregarPosicionable(this, this->posicion);
	avanzar(mapa);
	explotar(jugador, mapa);
}

void Cohete::avanzar(Mapa& mapa){
	this->posicion.increment_on_direction(this->direccion, 1);
	Posicionable* objeto = mapa.obtenerPosicionableEn(this->posicion);
	if (!static_cast<Jugador*>(objeto)) /* && no es un objeto */{
		avanzar(mapa);
	}
}

void Cohete::explotar(Jugador* jugador, Mapa& mapa){
	/* Recorrer jugadores calculando distancia */
}

	
