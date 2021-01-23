#include "Arma.h"

#include <ConfigVariable.h>
#include "Player.h"
#include "Mapa.h"
#include "ExceptionServer.h"
#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include <iostream>


#define PASO 1
#define ROTACION_45 0.7071
#define PORCENTAJE 100
#define DISTANCIA_CUCHILLO 2


// Cuchillo


void Cuchillo::disparar(Player* jugador, angulos_enemigos_t& enemigos){
	for (std::pair<int, Player*> e: enemigos){
		if (jugador->calcularDistancia(e.second) < DISTANCIA_CUCHILLO){
			int danio = rand() % (int)configs[CONFIG::maximo_danio] + 1;
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
    
	while (actual != fin && actual.calculate_distance(fin) > 0.3){
		if (mapa.hayObstaculoEn(actual) && actual != inicio)
			return true;
		actual.increment_on_direction(direccion, PASO);
	}
	return false;
}

void atacar(Player* jugador, Player* enemigo, float precision, int angulo){
	double distancia = jugador->calcularDistancia(enemigo);
		
    float danio = precision - 
                  distancia * configs[CONFIG::baja_precision_distancia];
	danio -= angulo/(int)configs[CONFIG::rango_de_disparo];
	int n_rand = rand() % (int)configs[CONFIG::maximo_danio] + 1;
	danio *= n_rand;
	bool murio = enemigo->recibirDanio(std::ceil(danio));
	if (murio)
		jugador->agregarEnemigoMuerto();
}


bool dispararBala(Player* jugador, float precision, int angulo, Player* enemigo){
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

void Pistola::disparar(Player* jugador, angulos_enemigos_t& enemigos){
	for (std::pair<int, Player*> e: enemigos){
		if (dispararBala(jugador, configs[CONFIG::precision_pistola],
		    e.first, e.second))
			return;
	}
}


// Ametralladora

void Ametralladora::disparar(Player* jugador, angulos_enemigos_t& enemigos){
	for (std::pair<int, Player*> e: enemigos){
		if (dispararBala(jugador, configs[CONFIG::precision_ametralladora],
		    e.first, e.second))
			return;
	}
}

bool Ametralladora::usar(Player* jugador){
	return jugador->agregarArma(this);
}


// Canion de Cadena

void CanionDeCadena::disparar(Player* jugador, angulos_enemigos_t& enemigos){
	for (std::pair<int, Player*> e: enemigos){
		if (dispararBala(jugador, configs[CONFIG::precision_canion], 
		    e.first, e.second))
			return;
	}
}

bool CanionDeCadena::usar(Player* jugador){
	return jugador->agregarArma(this);
}


// Lanzacohetes

void Lanzacohetes::disparar(Player* jugador, std::map<int, Player*>& enemigos){	
	throw RocketException();
}

bool Lanzacohetes::usar(Player* jugador){
	return jugador->agregarArma(this);
}
