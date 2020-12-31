#include "Arma.h"

#include "ParamReaderServer.h"
#include "Player.h"
#include "Mapa.h"
#include <cstdlib>
#include <ctime>
#include <typeinfo>

#define PASO 1
#define ROTACION_45 0.7071
#define PORCENTAJE 100
#define DISTANCIA_CUCHILLO 2


// Cuchillo


void Cuchillo::disparar(Player* jugador, angulos_enemigos_t& enemigos){
	for (std::pair<int, Player*> e: enemigos){
		if (jugador->calcularDistancia(e.second) < DISTANCIA_CUCHILLO){
		    srand (time(0));
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

	while (actual != fin){
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
	danio *= (int)configs[CONFIG::maximo_danio];
	bool murio = enemigo->recibirDanio(std::ceil(danio));
	if (murio)
		jugador->agregarEnemigoMuerto();
}


bool dispararBala(Player* jugador, float precision, int angulo, Player* enemigo){
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
	Coordinates posicion = jugador->get_coordinates();
	const Coordinates& dir = jugador->get_direction();
	posicion.increment_on_direction(dir, 1);
	Cohete cohete(posicion, dir);
	cohete.disparar(jugador, enemigos);
}

bool Lanzacohetes::usar(Player* jugador){
	return jugador->agregarArma(this);
}


// Cohete

Cohete::Cohete(Coordinates posicion, Coordinates dir): 
    Posicionable(posicion), direccion(dir) { 
}

void Cohete::disparar(Player* jugador, std::map<int, Player*>& enemigos){
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

void Cohete::explotar(Player* jugador, std::map<int, Player*>& enemigos){
    for (auto it = enemigos.begin(); it != enemigos.end(); ++it){
        auto* enemigo = it->second;
		double distancia = this->posicion.calculate_distance(
			enemigo->get_coordinates());
		
		if (distancia > (int)configs[CONFIG::distancia_explosion_cohete])
			continue;
		if (colisionaConObjeto(jugador->getMapa(), this->posicion,
			enemigo->get_coordinates()))
			continue;
			
        float danio = (int)configs[CONFIG::maximo_danio] * 
              (1 - distancia /(int)configs[CONFIG::distancia_explosion_cohete]);
		bool murio = enemigo->recibirDanio(std::ceil(danio));
		if (murio)
			jugador->agregarEnemigoMuerto();
	}	
}
	
