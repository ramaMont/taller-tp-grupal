#include "Soldado.h"

#include "Mapa.h"

#include <unistd.h>

#define BALAS_AMETRALLADORA 5
#define TIEMPO_AMETRALLADORA 3000000
#define BALAS_LANZACOHETES 5
#define TIEMPO_CANION 1000000
#define GRADOS_180 180
#define GRADOS_45 45
#define PI 3.14159265358979323846


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

void EstadoSoldado::disparar(std::vector<Jugador*>& enemigos){
	this->soldado->disparar(this->jugador, enemigos);
	if (!this->soldado->estaListo())
		this->soldado = &this->perro;
}


// Perro

Perro::Perro(int& n): Soldado(n){
}

void Perro::disparar(Jugador *jugador, std::vector<Jugador*>& enemigos){
	this->cuchillo.disparar(jugador);
}

void Perro::soltarArma(Jugador *jugador){
}

bool Perro::estaListo(){
	return true;
}


// Soldado

int radianesAGrados(double radianes){
	return radianes * GRADOS_180 / PI;
}

void Soldado::obtenerEnemigosCercanos(std::vector<Jugador*>& enemigos,
    Jugador* jugador, std::set<std::pair<int, Jugador*>>& jugadores){
	for (Jugador* enemigo: enemigos){
		if (enemigo == jugador)   // No definido
			continue;
		float angulo = jugador->get_coordinates().calculate_angle(
		    jugador->get_direction(), enemigo->get_coordinates());
		int grados = radianesAGrados(angulo);
		if (grados <= GRADOS_45)
		    jugadores.insert(std::pair<int,Jugador*>(grados,enemigo));
	}
}


// Guardia

Guardia::Guardia(int& balas): Soldado(balas){
}

void Guardia::disparar(Jugador *jugador, std::vector<Jugador*>& enemigos){
	std::set<std::pair<int, Jugador*>> set_jugadores;
	obtenerEnemigosCercanos(enemigos, jugador, set_jugadores);
	this->pistola.disparar(jugador, set_jugadores);
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

void SS::disparar(Jugador *jugador, std::vector<Jugador*>& enemigos){
	std::set<std::pair<int, Jugador*>> set_jugadores;
	obtenerEnemigosCercanos(enemigos, jugador, set_jugadores);
	for (int i = 0; (i < BALAS_AMETRALLADORA) && (this->balas > 0); i ++){
		this->ametralladora->disparar(jugador, set_jugadores);
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
	
void Oficial::disparar(Jugador *jugador, std::vector<Jugador*>& enemigos){
	std::set<std::pair<int, Jugador*>> set_jugadores;
	obtenerEnemigosCercanos(enemigos, jugador, set_jugadores);
	for (int i = 0; (i < 1/*tiempo presionado*/) && (this->balas > 0); i ++){
		this->canion->disparar(jugador, set_jugadores);
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

void Mutante::disparar(Jugador *jugador, std::vector<Jugador*>& enemigos){
	this->lanzacohetes->disparar(jugador, enemigos);
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

