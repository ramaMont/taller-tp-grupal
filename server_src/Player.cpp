#include "Player.h"
#include <ConfigVariable.h>

#include <iostream>
#include <algorithm>


Player::Player(Mapa& mapa, int id, BlockingQueue<Protocol>& game_model_queue):
		mapa(mapa), player_id(id), 
		soldado(this, this->balas_restantes),
		_game_model_queue(game_model_queue){
    mapa.agregarPlayer(this);
    this->vida = (int)configs[CONFIG::vida_maxima];
    this->vidasRestantes = (int)configs[CONFIG::cantidad_de_vidas];
    this->balas_restantes = (int)configs[CONFIG::balas_iniciales];
    this->puntuacion = 0;
    this->balas_disparadas = 0;
    this->enemigos_matados = 0;
    this->llave = false;  
    this->is_alive = true;
}

Player::Player(Coordinates position,Coordinates direction ,Mapa& mapa, 
	BlockingQueue<Protocol>& game_model_queue):
		Posicionable(position),direction(direction), mapa(mapa), player_id(0),
		soldado(this, this->balas_restantes), 
		posicion_inicial(posicion),	_game_model_queue(game_model_queue){
    mapa.agregarPlayer(this);
    this->vida = (int)configs[CONFIG::vida_maxima];
    this->vidasRestantes = (int)configs[CONFIG::cantidad_de_vidas];
    this->balas_restantes = (int)configs[CONFIG::balas_iniciales];
    this->puntuacion = 0;
    this->balas_disparadas = 0;
    this->enemigos_matados = 0;
    this->llave = false;  
    this->is_alive = true;
    atomic_dir(direction);
    atomic_pos(posicion);
}

Player::Player(Coordinates position,Coordinates direction ,Mapa& mapa, int id,
	BlockingQueue<Protocol>& game_model_queue):
		Posicionable(position),direction(direction), mapa(mapa), player_id(id),
		soldado(this, this->balas_restantes),
		posicion_inicial(posicion),
		_game_model_queue(game_model_queue){
    mapa.agregarPlayer(this);
    this->vida = (int)configs[CONFIG::vida_maxima];
    this->vidasRestantes = (int)configs[CONFIG::cantidad_de_vidas];
    this->balas_restantes = (int)configs[CONFIG::balas_iniciales];
    this->puntuacion = 0;
    this->balas_disparadas = 0;
    this->enemigos_matados = 0;
    this->llave = false;  
    this->is_alive = true;
    atomic_dir(direction);
    atomic_pos(posicion);
}

void Player::mover(Direccion* direccion){
    Coordinates nuevaPos = direccion->mover(this,direction);
    try{
        mapa.moveme(this, nuevaPos);
        this->posicion = nuevaPos;
    } catch(...){
        Coordinates movimiento_unidireccional;
        movimiento_unidireccional.x = nuevaPos.x;
        movimiento_unidireccional.y = this->posicion.y;
        try{
            mapa.moveme(this, movimiento_unidireccional);
            this->posicion = movimiento_unidireccional;
        } catch(...){
        }

        movimiento_unidireccional.x = this->posicion.x;
        movimiento_unidireccional.y = nuevaPos.y;
        try{
            mapa.moveme(this, movimiento_unidireccional);
            this->posicion = movimiento_unidireccional;
        } catch(...){
        }
    }
    atomic_pos(posicion);
}

Coordinates Player::get_coordinates() const{
    return posicion;
}

Coordinates Player::get_direction() const{
    return direction;
}

void Player::set_direction(Coordinates direction){
    this->direction = direction;
    atomic_dir(this->direction);
}

void Player::set_direction(std::string direction){
	Coordinates player_direction(direction);
    this->direction = player_direction;
    this->initial_direction = player_direction;
    atomic_dir(this->direction);
}

int Player::getId(){
    return player_id;
}

double Player::calcularAngulo(Player* jugador){
	return jugador->calcularAngulo(this->direction, this->posicion);
}

double Player::calcularAngulo(const Coordinates& direccion, const Coordinates& other_pos){
	return other_pos.calculate_angle(direccion, this->posicion);
}

double Player::calcularDistancia(Player* jugador){
	return jugador->calcularDistancia(this->posicion);
}

double Player::calcularDistancia(const Coordinates& posicion){
	return posicion.calculate_distance(this->posicion);
}

bool Player::recibirDanio(int danio){
	this->vida = std::max(this->vida - danio, 0);
	Protocol protocol(player_id, vida, Protocol::action::SHOOTED);
	_game_model_queue.push(protocol);
	if (this->vida <= 0){
		Protocol protocol(player_id);
		protocol.setAction(Protocol::action::DIE);
		_game_model_queue.push(protocol);
		return true;
	}
	return false;
}

void Player::disparar(std::map<int, Player*>& jugadores){
	this->balas_disparadas += this->soldado.disparar(jugadores);
	Protocol protocol(player_id, balas_restantes, Protocol::action::UPDATE_BULLETS);
	_game_model_queue.push(protocol);
}

bool Player::usar(Item* item){
    bool b = item->usar(this);
    if (b){
        Coordinates& position = item->getPosition();
        Protocol protocol(Protocol::action::PICKUP, player_id,
            Protocol::direction::STAY, 0, position.x, position.y);    
        _game_model_queue.push(protocol);
    }
    return b;
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
	Protocol protocol(player_id, vida, Protocol::action::UPDATE_HEALTH);
	_game_model_queue.push(protocol);
	return true;
}
	
void Player::agregarPuntos(int cantidad){
	this->puntuacion += cantidad;
	Protocol protocol(player_id, cantidad, Protocol::action::ADDPOINTS);
	_game_model_queue.push(protocol);
}

bool Player::agregarBalas(int cant){
	if (this->balas_restantes == (int)configs[CONFIG::balas_maximas])
		return false;
	this->balas_restantes = std::min(this->balas_restantes+cant, 
	    (int)configs[CONFIG::balas_maximas]);
	this->soldado.recargarBalas();
	Protocol protocol(player_id, balas_restantes, Protocol::action::UPDATE_BULLETS);
	_game_model_queue.push(protocol);
	return true;
}

bool Player::agregarLlave(){
	if (this->llave)
		return false;
	this->llave = true;
    //TODO: Agregar protocolo de que se agrego una llave.
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
    this->vidasRestantes --;
	mapa.sacarPosicionable(this->posicion);	
	throwGun();
	throwBullets();
	if (this->llave)
		throwKey();
	if (this->vidasRestantes > 0){
		Protocol protocol(player_id);
		protocol.setAction(Protocol::action::RESURRECT);
		_game_model_queue.push(protocol);
	}else{
        this->is_alive = false;
    }
}

bool Player::revivir(){
    this->posicion = posicion_inicial;
    this->direction = initial_direction;
    mapa.respawnPlayer(this);
    this->vida = (int)configs[CONFIG::vida_maxima];
    this->balas_restantes = (int)configs[CONFIG::balas_iniciales];
    this->soldado.cambiarArma(N_PISTOLA);
    atomic_dir(this->direction);
    atomic_pos(this->posicion);
    return true;
}
bool Player::estaVivo(){
	return this->is_alive;
}

Mapa& Player::getMapa(){
	return this->mapa;
}

int Player::numeroArmaActual(){
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

void Player::setPosition(Coordinates position){
	this->posicion = position;
	this->posicion_inicial = position;
	atomic_pos(this->posicion);
}

void Player::throwGun(){
    int i = this->soldado.soltarArma();
    if (i <= 0)
        return;
    Protocol protocol(Protocol::action::THROW, i,
        Protocol::direction::STAY, 0, posicion.x, posicion.y);    
    _game_model_queue.push(protocol);
}

void Player::throwBullets(){
    Balas* bullets = new Balas(this->posicion, 10);
    Coordinates pos = this->mapa.throwItem(bullets, this->posicion);
    bullets->setPosition(pos);
    Protocol protocol(Protocol::action::THROW, 10,
        Protocol::direction::STAY, 0, pos.x, pos.y);    
    _game_model_queue.push(protocol);
}

void Player::throwKey(){
    Llave* key = new Llave(this->posicion);
    Coordinates pos = this->mapa.throwItem(key, this->posicion);
    key->setPosition(pos);
    this->llave = false;
    Protocol protocol(Protocol::action::THROW, 7,
        Protocol::direction::STAY, 0, pos.x, pos.y);    
    _game_model_queue.push(protocol);
}


AtomicCoordinates& Player::getAtomicDirection(){
    return atomic_dir;
}

AtomicCoordinates& Player::getAtomicPosition(){
    return atomic_pos;
}

Player::~Player(){
}
