#include "Player.h"
#include <ConfigVariable.h>

#include <iostream>
#include <algorithm>
#include <string>
#include <map>


Player::Player(ServerMap& map, int id, BlockingQueue<Protocol>& 
    game_model_queue):
		map(map), player_id(id), 
		soldier(this, bullets, game_model_queue),
		_game_model_queue(game_model_queue){
    map.addPlayer(this);
    health = (int)configs[CONFIG::vida_maxima];
    lives = (int)configs[CONFIG::cantidad_de_vidas];
    bullets = (int)configs[CONFIG::balas_iniciales];
    score = 0;
    fired_bullets = 0;
    killed_enemies = 0;
    keys = 0;  
    is_alive = true;
}

Player::Player(Coordinates position,Coordinates direction ,ServerMap& map, 
	BlockingQueue<Protocol>& game_model_queue):
		Posicionable(position, direction), map(map), player_id(0),
		soldier(this, bullets, game_model_queue), 
		posicion_inicial(posicion),	_game_model_queue(game_model_queue){
    map.addPlayer(this);
    health = (int)configs[CONFIG::vida_maxima];
    lives = (int)configs[CONFIG::cantidad_de_vidas];
    bullets = (int)configs[CONFIG::balas_iniciales];
    score = 0;
    fired_bullets = 0;
    killed_enemies = 0;
    keys = 0;  
    is_alive = true;
    atomic_dir(direction);
    atomic_pos(posicion);
}

Player::Player(Coordinates position,Coordinates direction ,ServerMap& map, 
    int id,	BlockingQueue<Protocol>& game_model_queue):
		Posicionable(position, direction), map(map), player_id(id),
		soldier(this, bullets, game_model_queue),
		posicion_inicial(posicion),
		_game_model_queue(game_model_queue){
    map.addPlayer(this);
    health = (int)configs[CONFIG::vida_maxima];
    lives = (int)configs[CONFIG::cantidad_de_vidas];
    bullets = (int)configs[CONFIG::balas_iniciales];
    score = 0;
    fired_bullets = 0;
    killed_enemies = 0;
    keys = 0;  
    is_alive = true;
    atomic_dir(direction);
    atomic_pos(posicion);
}

void Player::mover(Direction* _direction){
    Coordinates new_pos = _direction->move(this,direction);
    try{
        map.moveme(this, new_pos);
        this->posicion = new_pos;
    } catch(...){
        Coordinates movimiento_unidireccional;
        movimiento_unidireccional.x = new_pos.x;
        movimiento_unidireccional.y = this->posicion.y;
        try{
            map.moveme(this, movimiento_unidireccional);
            this->posicion = movimiento_unidireccional;
        } catch(...){
        }

        movimiento_unidireccional.x = this->posicion.x;
        movimiento_unidireccional.y = new_pos.y;
        try{
            map.moveme(this, movimiento_unidireccional);
            this->posicion = movimiento_unidireccional;
        } catch(...){
        }
    }
    atomic_pos(posicion);
}

Coordinates Player::get_coordinates(){
    return posicion;
}

Coordinates Player::get_direction(){
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

double Player::calculateAngle(Player* player){
	return player->calculateAngle(this->direction, this->posicion);
}

double Player::calculateAngle(const Coordinates& direccion, 
        const Coordinates& other_pos){
	return other_pos.calculate_angle(direccion, this->posicion);
}

double Player::calculateDistance(Player* player){
	return player->calculateDistance(this->posicion);
}

double Player::calculateDistance(const Coordinates& posicion){
	return posicion.calculate_distance(this->posicion);
}

bool Player::hurt(int damage){
    if (this->health <= 0){
        return false;
    }
    this->health = std::max(health - damage, 0);
	Protocol protocol(player_id, health, Protocol::action::SHOOTED);
	_game_model_queue.push(protocol);
	if (health <= 0){
		Protocol protocol(player_id);
		protocol.setAction(Protocol::action::DIE);
		_game_model_queue.push(protocol);
		return true;
	}
	return false;
}

bool Player::shoot(std::map<int, Player*>& players){
    int bullets_before = bullets;
    int result = soldier.shoot(players);
	fired_bullets += bullets_before - bullets;
	Protocol protocol(player_id, bullets, Protocol::action::UPDATE_BULLETS);
	_game_model_queue.push(protocol);
    return result == 0;
}

bool Player::use(Item* item){
    bool b = item->use(this);
    if (b){
        Coordinates position = item->getPosicion();
        map.removeItem(position);
        Protocol protocol(Protocol::action::PICKUP, player_id,
            Protocol::direction::STAY, 0, position.x, position.y);    
        _game_model_queue.push(protocol);
    }
    return b;
}

bool Player::addGun(int gun_number){
	return soldier.addGun(gun_number);
}

void Player::switchGun(int gun_number){
	soldier.switchGun(gun_number);
}

bool Player::addHealth(int amount){
	if (health == (int)configs[CONFIG::vida_maxima])
		return false;
	health = std::min(health + amount, (int)configs[CONFIG::vida_maxima]);
	Protocol protocol(player_id, health, Protocol::action::UPDATE_HEALTH);
	_game_model_queue.push(protocol);
	return true;
}
	
void Player::addScore(int amount){
	score += amount;
	Protocol protocol(player_id, amount, Protocol::action::ADDPOINTS);
	_game_model_queue.push(protocol);
}

bool Player::addBullets(int amount){
	if (bullets == (int)configs[CONFIG::balas_maximas])
		return false;
	bullets = std::min(bullets + amount, (int)configs[CONFIG::balas_maximas]);
	soldier.rechargeBullets();
	Protocol protocol(player_id, bullets, Protocol::action::UPDATE_BULLETS);
	_game_model_queue.push(protocol);
	return true;
}

bool Player::addKey(){
    if (keys > 1) return false;
	keys ++;
    Protocol protocol(player_id, keys, Protocol::action::KEY);
    _game_model_queue.push(protocol);
	return true;
}

bool Player::useKey(){
    if (keys == 0) return false;
	keys --;
    Protocol protocol(player_id, keys, Protocol::action::KEY);
	_game_model_queue.push(protocol);
	return true;
}

void Player::addKilledEnemy(){
	killed_enemies ++;
}

bool Player::lowHealth(){
	return health <= (int)configs[CONFIG::vida_minima];
}

void Player::die(){
    lives --;
	throwGun();
	throwBullets();
	if (keys > 0)
		throwKey();
	map.removePosicionable(this->posicion);	
	if (lives > 0){
		Protocol protocol(player_id);
		protocol.setAction(Protocol::action::RESURRECT);
		_game_model_queue.push(protocol);
	}else{
        this->is_alive = false;
    }
}

bool Player::revive(){
    this->posicion = posicion_inicial;
    this->direction = initial_direction;
    map.respawnPlayer(this);
    health = (int)configs[CONFIG::vida_maxima];
    bullets = (int)configs[CONFIG::balas_iniciales];
    soldier.rechargeBullets();
    atomic_dir(this->direction);
    atomic_pos(this->posicion);
    return true;
}
bool Player::isAlive(){
	return is_alive;
}

ServerMap& Player::getMap(){
	return map;
}

int Player::actualGun(){
	return soldier.actualGun();
}

size_t Player::getFiredBullets(){
	return fired_bullets;
}

size_t Player::getKilledEnemies(){
	return killed_enemies;
}

size_t Player::getScore(){
	return score;
}

void Player::setPosition(Coordinates position){
	this->posicion = position;
	this->posicion_inicial = position;
	atomic_pos(this->posicion);
}

void Player::throwGun(){
    Coordinates pos = map.getEmptyPosition(posicion);
    if (pos.x < 0 || pos.y < 0) return;
    int i = soldier.throwGun(pos);
    if (i <= 0)
        return;
    Protocol protocol(Protocol::action::THROW, i,
        Protocol::direction::STAY, 0, pos.x, pos.y);    
    _game_model_queue.push(protocol);
}

void Player::throwBullets(){
    Coordinates pos = map.getEmptyPosition(posicion);
    if (pos.x < 0 || pos.y < 0) return;
    Bullets* new_bullets = new Bullets(pos, 10);
    map.addItem(new_bullets, pos);
    Protocol protocol(Protocol::action::THROW, 10,
        Protocol::direction::STAY, 0, pos.x, pos.y);    
    _game_model_queue.push(protocol);
}

void Player::throwKey(){
    for (int i = 0; i < keys; i++){
        Coordinates pos = map.getEmptyPosition(posicion);
        if (pos.x < 0 || pos.y < 0) return;
        Key* new_key = new Key(pos);
        map.addItem(new_key, pos);
        Protocol protocol(Protocol::action::THROW, 7,
            Protocol::direction::STAY, 0, pos.x, pos.y);    
        _game_model_queue.push(protocol);
    }
    keys = 0;
    Protocol protocol(player_id, keys, Protocol::action::KEY);
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
