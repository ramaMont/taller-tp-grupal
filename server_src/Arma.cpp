#include "Arma.h"

#include "ParamReaderServer.h"
#include "Jugador.h"
#include <cstdlib>
#include <ctime>
#include <typeinfo>

#include <iostream>

#define PASO 1
#define ROTACION_45 0.7071
#define PORCENTAJE 100
#define DISTANCIA_CUCHILLO 2


// Cuchillo


void Cuchillo::disparar(Jugador* jugador, angulos_enemigos_t& enemigos){
	for (std::pair<int, Jugador*> e: enemigos){
		if (jugador->calcularDistancia(e.second) < DISTANCIA_CUCHILLO){
		    srand (time(0));
			int danio = rand() % (int)configuracion["maximo_danio"] + 1;
			bool murio = e.second->recibirDanio(danio);
			if (murio)
				jugador->agregarEnemigoMuerto();
			return;
		}
	}
}


// Arma

bool colisionaConObjeto(Mapa& mapa, const Coordinates& inicio, 
    const Coordinates& fin){
	if (inicio == fin) return false;
	Coordinates direccion(fin.x - inicio.x, fin.y - inicio.y);
	Coordinates actual(inicio.x, inicio.y);
	direccion.normalice_direction();
	actual.increment_on_direction(direccion, PASO);

	while (actual != fin){
		if (mapa.hayObstaculoEn(actual) && actual != inicio)
			return true;
		actual.increment_on_direction(direccion, PASO);
	}
	return false;
}

void atacar(Jugador* jugador, Jugador* enemigo, float precision, int angulo){
	double distancia = jugador->calcularDistancia(enemigo);
		
    float danio = precision - 
                  distancia * configuracion["baja_de_precision_por_distancia"];
	danio -= angulo/(int)configuracion["rango_de_disparo"];
	danio *= (int)configuracion["maximo_danio"];
	bool murio = enemigo->recibirDanio(std::ceil(danio));
	if (murio)
		jugador->agregarEnemigoMuerto();
}


bool dispararBala(Jugador* jugador, float precision, int angulo, Jugador* enemigo){
	srand (time(NULL));
	int n_rand = rand() % PORCENTAJE;
	if ((n_rand / PORCENTAJE) > precision)	// Falla el tiro
		return true;
		
	if (colisionaConObjeto(jugador->getMapa(), jugador->get_coordinates(),
	    enemigo->get_coordinates()))	// Hay un objeto en el medio
	    return false;

    atacar(jugador, enemigo, precision, angulo);	
    return true;
}

// Pistola

void Pistola::disparar(Jugador* jugador, angulos_enemigos_t& enemigos){
	for (std::pair<int, Jugador*> e: enemigos){
		if (dispararBala(jugador, configuracion["precision_pistola"],
		    e.first, e.second))
			return;
	}
}


// Ametralladora

void Ametralladora::disparar(Jugador* jugador, angulos_enemigos_t& enemigos){
	for (std::pair<int, Jugador*> e: enemigos){
		if (dispararBala(jugador, configuracion["precision_ametralladora"],
		    e.first, e.second))
			return;
	}
}

bool Ametralladora::usar(Jugador* jugador){
	return jugador->agregarArma(this);
}


// Canion de Cadena

void CanionDeCadena::disparar(Jugador* jugador, angulos_enemigos_t& enemigos){
	for (std::pair<int, Jugador*> e: enemigos){
		if (dispararBala(jugador, configuracion["precision_canion"], 
		    e.first, e.second))
			return;
	}
}

bool CanionDeCadena::usar(Jugador* jugador){
	return jugador->agregarArma(this);
}


// Lanzacohetes

void Lanzacohetes::disparar(Jugador* jugador, std::vector<Jugador*>& enemigos){	
	Coordinates posicion = jugador->get_coordinates();
	const Coordinates& dir = jugador->get_direction();
	posicion.increment_on_direction(dir, 1);
	Cohete cohete(posicion, dir);
	cohete.disparar(jugador, enemigos);
}

bool Lanzacohetes::usar(Jugador* jugador){
	return jugador->agregarArma(this);
}


// Cohete

Cohete::Cohete(Coordinates posicion, Coordinates dir): 
    Posicionable(posicion), direccion(dir) { 
}

void Cohete::disparar(Jugador* jugador, std::vector<Jugador*>& enemigos){
	Mapa& mapa = jugador->getMapa();
	mapa.agregarPosicionable(this, this->posicion);
	avanzar(mapa);
	explotar(jugador, enemigos);
}

void Cohete::avanzar(Mapa& mapa){
	mapa.sacarPosicionable(this->posicion);
	this->posicion.increment_on_direction(this->direccion, 1);
	if (mapa.hayObstaculoEn(this->posicion))
        return;
    mapa.agregarPosicionable(this, this->posicion);
	return avanzar(mapa);
}

void Cohete::explotar(Jugador* jugador, std::vector<Jugador*>& enemigos){
	for (Jugador* enemigo: enemigos){
		double distancia = this->posicion.calculate_distance(
			enemigo->get_coordinates());
		
		if (distancia > (int)configuracion["distancia_explosion_cohete"])
			continue;
		if (colisionaConObjeto(jugador->getMapa(), this->posicion,
			enemigo->get_coordinates()))
			continue;
			
        float danio = (int)configuracion["maximo_danio"] * 
              (1 - distancia /(int)configuracion["distancia_explosion_cohete"]);
		bool murio = enemigo->recibirDanio(std::ceil(danio));
		if (murio)
			jugador->agregarEnemigoMuerto();
	}	
}
	
