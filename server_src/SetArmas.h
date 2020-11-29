#ifndef __SET_ARMAS__
#define __SET_ARMAS__

class Mapa;

#include "Arma.h"

class SetArmas {
	private:
	Cuchillo cuchillo;
	Pistola pistola;
	Ametralladora* ametralladora;
	bool tengo_ametralladora;
	CanionDeCadena* canion;
	bool tengo_canion;
	Lanzacohetes* lanzacohetes;
	bool tengo_lanzacohetes;
	
	public:
	explicit SetArmas(Posicion posicion);
	// Retorna true en caso de agregar una nueva arma
	// Retorna false en caso de que ya tenga esa arma o sea un numero invalido
	bool agregarArma(int numero_arma, Arma* arma);
	bool agregarArma(Arma* arma);
	// Deja en el mapa las armas 
	void soltarArmas(Mapa &mapa);
	
	Arma* obtenerArma(int numero_arma);
	~SetArmas();
};

#endif
