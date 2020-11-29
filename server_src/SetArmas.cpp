#include "SetArmas.h"

#include "Mapa.h"

SetArmas::SetArmas(Posicion posicion):
    ametralladora(nullptr), canion(nullptr), lanzacohetes(nullptr){
	this->tengo_ametralladora = false;
	this->tengo_canion = false;
	this->tengo_lanzacohetes = false;
}


bool SetArmas::agregarArma(int numero_arma, Arma* arma){
	switch (numero_arma){
		case N_AMETRALLADORA:
			this->tengo_ametralladora = true;
			this->ametralladora = static_cast<Ametralladora*>(arma);
			return true;
		case N_CANION:
			this->tengo_canion = true;
			this->canion = static_cast<CanionDeCadena*>(arma);
			return true;
		case N_LANZACOHETES:
			this->tengo_lanzacohetes = true;
			this->lanzacohetes = static_cast<Lanzacohetes*>(arma);
			return true;
	}
	return false;
}


bool SetArmas::agregarArma(Arma* arma){
	if (static_cast<Ametralladora*>(arma)){
		this->ametralladora = static_cast<Ametralladora*>(arma);
		return true;
	}
	if (static_cast<CanionDeCadena*>(arma)){
		this->canion = static_cast<CanionDeCadena*>(arma);
		return true;
	}
	if (static_cast<Lanzacohetes*>(arma)){
		this->lanzacohetes = static_cast<Lanzacohetes*>(arma);
		return true;
	}
	return false;
}

void SetArmas::soltarArmas(Mapa &mapa){
	if (this->tengo_ametralladora)
		mapa.soltar(this->ametralladora);
	if (this->tengo_canion)
		mapa.soltar(this->canion);
	if (this->tengo_lanzacohetes)
		mapa.soltar(this->lanzacohetes);
	this->tengo_ametralladora = false;
	this->tengo_canion = false;
	this->tengo_lanzacohetes = false;
}

Arma* SetArmas::obtenerArma(int numero_arma){
	switch (numero_arma){
		case N_PISTOLA:
			return &this->pistola;
		case N_AMETRALLADORA:
			if (this->tengo_ametralladora)
				return this->ametralladora;
		case N_CANION:
			if (this->tengo_canion)
				return this->canion;
		case N_LANZACOHETES:
			if (this->tengo_lanzacohetes)
				return this->lanzacohetes;
	}
	return &this->cuchillo;
}


SetArmas::~SetArmas(){
}


