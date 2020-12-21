#include "Objeto.h"

#include "ParamReaderServer.h"
#include <thread>
#include <chrono>


void ParedFalsa::abrir(Jugador *jugador){
	if (jugador->get_coordinates().calculate_distance(this->posicion) <= 1)
		jugador->getMapa().sacarPosicionable(this->posicion);
}


void Puerta::abrir(Jugador *jugador){
    abrirPuerta(jugador);
}

void Puerta::abrirPuerta(Jugador *jugador){
	if (jugador->get_coordinates().calculate_distance(this->posicion) > 1)
		return;
	atravesable(true);
	
	// Cambiar a un evento
	std::this_thread::sleep_for (std::chrono::seconds(
	    (int)configuracion["segundos_cerrar_puerta"]));
	cerrar();	
}

void Puerta::cerrar(){
	atravesable(false);
}


void PuertaCerrada::abrir(Jugador *jugador){
	if (this->llave || jugador->usarLlave())
		abrirPuerta(jugador);
}
		
