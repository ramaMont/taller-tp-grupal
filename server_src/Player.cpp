#include "Player.h"
#include <ConfigVariable.h>

#include <iostream>
#include <algorithm>


Player::Player(Mapa& map, int id, BlockingQueue<Protocol>& game_model_queue):
		map(map), player_id(id), 
		soldier(this, bullets),
		_game_model_queue(game_model_queue){
    map.addPlayer(this);
    health = (int)configs[CONFIG::vida_maxima];
    lives = (int)configs[CONFIG::cantidad_de_vidas];
    bullets = (int)configs[CONFIG::balas_iniciales];
    score = 0;
    fired_bullets = 0;
    killed_enemies = 0;
    key = false;  
    is_alive = true;
}

Player::Player(Coordinates position,Coordinates direction ,Mapa& map, 
	BlockingQueue<Protocol>& game_model_queue):
		Posicionable(position),direction(direction), map(map), player_id(0),
		soldier(this, bullets), 
		posicion_inicial(posicion),	_game_model_queue(game_model_queue){
    map.addPlayer(this);
    health = (int)configs[CONFIG::vida_maxima];
    lives = (int)configs[CONFIG::cantidad_de_vidas];
    bullets = (int)configs[CONFIG::balas_iniciales];
    score = 0;
    fired_bullets = 0;
    killed_enemies = 0;
    key = false;  
    is_alive = true;
    atomic_dir(direction);
    atomic_pos(posicion);
}

Player::Player(Coordinates position,Coordinates direction ,Mapa& map, int id,
	BlockingQueue<Protocol>& game_model_queue):
		Posicionable(position),direction(direction), map(map), player_id(id),
		soldier(this, bullets),
		posicion_inicial(posicion),
		_game_model_queue(game_model_queue){
    map.addPlayer(this);
    health = (int)configs[CONFIG::vida_maxima];
    lives = (int)configs[CONFIG::cantidad_de_vidas];
    bullets = (int)configs[CONFIG::balas_iniciales];
    score = 0;
    fired_bullets = 0;
    killed_enemies = 0;
    key = false;  
    is_alive = true;
    atomic_dir(direction);
    atomic_pos(posicion);
}

void Player::mover(Direccion* _direction){
    Coordinates new_pos = _direction->mover(this,direction);
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

double Player::calculateAngle(Player* player){
	return player->calculateAngle(this->direction, this->posicion);
}

double Player::calculateAngle(const Coordinates& direccion, const Coordinates& other_pos){
	return other_pos.calculate_angle(direccion, this->posicion);
}

double Player::calculateDistance(Player* player){
	return player->calculateDistance(this->posicion);
}

double Player::calculateDistance(const Coordinates& posicion){
	return posicion.calculate_distance(this->posicion);
}

bool Player::hurt(int damage){
	health = std::max(health - damage, 0);
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

void Player::shoot(std::map<int, Player*>& players){
	fired_bullets += soldier.shoot(players);
	Protocol protocol(player_id, bullets, Protocol::action::UPDATE_BULLETS);
	_game_model_queue.push(protocol);
}

bool Player::use(Item* item){
    bool b = item->use(this);
    if (b){
        Coordinates& position = item->getPosition();
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
    bool had_key = key;
	key = true;
	return !had_key;
}

bool Player::useKey(){
	bool had_key = key;
	key = false;
	return had_key;
}

void Player::addKilledEnemy(){
	killed_enemies ++;
}

bool Player::lowHealth(){
	return health <= (int)configs[CONFIG::vida_minima];
}

void Player::die(){
    lives --;
	map.removePosicionable(this->posicion);	
	throwGun();
	throwBullets();
	if (this->key)
		throwKey();
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
    soldier.switchGun(0);
    atomic_dir(this->direction);
    atomic_pos(this->posicion);
    return true;
}
bool Player::isAlive(){
	return is_alive;
}

Mapa& Player::getMap(){
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
    int i = soldier.throwGun();
    if (i <= 0)
        return;
    Protocol protocol(Protocol::action::THROW, i,
        Protocol::direction::STAY, 0, posicion.x, posicion.y);    
    _game_model_queue.push(protocol);
}

void Player::throwBullets(){
    Bullets* bullets = new Bullets(this->posicion, 10);
    Coordinates pos = this->map.throwItem(bullets, this->posicion);
    bullets->setPosition(pos);
    Protocol protocol(Protocol::action::THROW, 10,
        Protocol::direction::STAY, 0, pos.x, pos.y);    
    _game_model_queue.push(protocol);
}

void Player::throwKey(){
    Key* new_key = new Key(this->posicion);
    Coordinates pos = this->map.throwItem(new_key, this->posicion);
    new_key->setPosition(pos);
    key = false;
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
