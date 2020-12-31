#include "Player.h"
#include "ParamReaderServer.h"
//#include "Mapa.h"
#include <stdio.h>
#include <algorithm>


Player::Player(Coordinates position,Coordinates direction ,Mapa& mapa, 
		BlockingQueue<Protocol>& game_model_queue):
    Posicionable(position),direction(direction), mapa(mapa), player_id(0),
    soldado(EstadoSoldado(this, this->balas_restantes)), 
	_game_model_queue(game_model_queue){
    mapa.agregarPlayer(this);
    this->vida = (int)configs[CONFIG::vida_maxima];
    this->vidasRestantes = (int)configs[CONFIG::cantidad_de_vidas];
    this->balas_restantes = (int)configs[CONFIG::balas_iniciales];
    this->puntuacion = 0;
    this->balas_disparadas = 0;
    this->enemigos_matados = 0;
    this->llave = false;  
}

Player::Player(Coordinates position,Coordinates direction ,Mapa& mapa, int id,
		BlockingQueue<Protocol>& game_model_queue):
    Posicionable(position),direction(direction), mapa(mapa), player_id(id),
    soldado(EstadoSoldado(this, this->balas_restantes)),
	_game_model_queue(game_model_queue){
    mapa.agregarPlayer(this);
    this->vida = (int)configs[CONFIG::vida_maxima];
    this->vidasRestantes = (int)configs[CONFIG::cantidad_de_vidas];
    this->balas_restantes = (int)configs[CONFIG::balas_iniciales];
    this->puntuacion = 0;
    this->balas_disparadas = 0;
    this->enemigos_matados = 0;
    this->llave = false;  
}

void Player::mover(Direccion* direccion){
    Coordinates nuevaPos = direccion->mover(this,direction);
    try{
        mapa.moveme(this, nuevaPos);
        this->posicion = nuevaPos;
    } catch(...){
    }
}

Coordinates Player::get_coordinates() const{
    return posicion;
}

Coordinates Player::get_direction() const{
    return direction;
}

void Player::set_direction(Coordinates direction){
    this->direction = direction;
}

int Player::getId(){
    return player_id;
}

double Player::calcularAngulo(Player* jugador){
	return jugador->calcularAngulo(this->direction, this->posicion);
}

double Player::calcularAngulo(const Coordinates& direccion, const Coordinates& posicion){
	return posicion.calculate_angle(direccion, this->posicion);
}

double Player::calcularDistancia(Player* jugador){
	return jugador->calcularDistancia(this->posicion);
}

double Player::calcularDistancia(const Coordinates& posicion){
	return posicion.calculate_distance(this->posicion);
}

bool Player::recibirDanio(int danio){
	this->vida = std::max(this->vida - danio, 0);
	Protocol protocol(player_id, danio, Protocol::action::SHOOTED);
	_game_model_queue.push(protocol);
	if (this->vida == 0){
		Protocol protocol(player_id);
		protocol.setAction(Protocol::action::DIE);
		_game_model_queue.push(protocol);
		return true;
	}
	return false;
}

void Player::disparar(std::map<int, Player*>& jugadores){
	this->soldado.disparar(jugadores);
}

bool Player::usar(Item* item){
	return item->usar(this);
}

bool Player::agregarArma(Arma* arma){
	return this->soldado.agregarArma(arma);
}

void Player::cambiarArma(int numero_arma){
	this->soldado.cambiarArma(numero_arma);
}

bool Player::agregarVida(int cantidad){
	if (this->vida == (int)configs[CONFIG::vida_maxima])
		return false;
	this->vida = std::min(this->vida + cantidad, (int)configs[CONFIG::vida_maxima]);
	return true;
}
	
void Player::agregarPuntos(int cantidad){
	this->puntuacion += cantidad;
}

bool Player::agregarBalas(int cant){
	if (this->balas_restantes == (int)configs[CONFIG::balas_maximas])
		return false;
	this->balas_restantes = std::min(this->balas_restantes+cant, 
	    (int)configs[CONFIG::balas_maximas]);
	this->soldado.recargarBalas();
	return true;
}

bool Player::agregarLlave(){
	if (this->llave)
		return false;
	this->llave = true;
	return true;
}

bool Player::usarLlave(){
	bool aux = this->llave;
	this->llave = false;
	return aux;
}

void Player::agregarEnemigoMuerto(){
	this->enemigos_matados ++;
}

bool Player::estaPorMorir(){
	return this->vida <= (int)configs[CONFIG::vida_minima];
}

void Player::morir(){
	this->soldado.soltarArma();
	this->mapa.soltar(Balas(this->posicion, 10));
	mapa.sacarPosicionable(this->posicion);
	if (this->llave){
		this->mapa.soltar(Llave(this->posicion));
		this->llave = false;
	}
	if (this->vidasRestantes > 0){
		Protocol protocol(player_id);
		protocol.setAction(Protocol::action::RESURRECT);
		_game_model_queue.push(protocol);
	}
}

bool Player::revivir(){
    mapa.agregarPosicionable(this, posicion_inicial);
    this->vida = (int)configs[CONFIG::vida_maxima];
    this->vidasRestantes --;
    this->balas_restantes = (int)configs[CONFIG::balas_iniciales];
    this->soldado.cambiarArma(N_PISTOLA);
    return true;
}

bool Player::estaVivo(){
	return ((this->vida > 0) || (this->vidasRestantes > 0));
}

Mapa& Player::getMapa(){
	return this->mapa;
}

int Player::numeroArmaActual() const{
	return this->soldado.armaActual();
}

size_t Player::getBalasDisparadas(){
	return this->balas_disparadas;
}

size_t Player::getEnemigosMatados(){
	return this->enemigos_matados;
}

size_t Player::getPuntuacion(){
	return this->puntuacion;
}

int Player::getVida(){
	return this->vida;
}

int Player::getBalas(){
	return this->balas_restantes;
}


Player::~Player(){
}


