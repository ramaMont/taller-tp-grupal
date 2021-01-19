#include "Protocol.h"
#include<arpa/inet.h>

Protocol::Protocol():
    _action(Protocol::action::NONE), id(0), 
    _direction(Protocol::direction::STAY), damage(0), _game_id(0), _float_aux(0){
}

Protocol::Protocol(int id):
    _action(Protocol::action::NONE), id(id), 
    _direction(Protocol::direction::STAY), damage(0), _game_id(0), _float_aux(0){
}

Protocol::Protocol(int user_id, int map_id):
    _action(Protocol::action::NONE), id(user_id), 
    _direction(Protocol::direction::STAY), damage(map_id), _game_id(0), _float_aux(0){
}

Protocol::Protocol(int user_id, int danio, Protocol::action action):
    _action(action), id(user_id), 
    _direction(Protocol::direction::STAY), damage(danio), _game_id(0), _float_aux(0){
}

Protocol::Protocol(int user_id, int map_id, int game_id):
    _action(Protocol::action::NONE), id(user_id), 
    _direction(Protocol::direction::STAY), damage(map_id), _game_id(game_id), _float_aux(0){
}

Protocol::Protocol(int id, Protocol::direction direction):
        _action(Protocol::action::MOVE), id(id), _direction(direction),
        damage(0), _game_id(0), _float_aux(0){
}

Protocol::Protocol(int config_number, float config_value):
        _action(Protocol::action::CONFIG), id(config_number),
        _direction(Protocol::direction::STAY), damage(0),
        _game_id(0), _float_aux(config_value){
}

Protocol::action Protocol::getAction(){
    return _action;
}
int Protocol::getId(){
    return id;
}
int Protocol::getMapId(){
    return damage;
}

int Protocol::getUserId(){
    return id;
}
int Protocol::getGameId(){
    return _game_id;
}
int Protocol::getDamage(){
    return damage;
}

Protocol::direction Protocol::getDirection(){
    return _direction;
}

int Protocol::getConfId(){
    return id;
}

int Protocol::getBotsCty(){
    return id;
}

float Protocol::getConfiguration(){
    return _float_aux;
}

void Protocol::moveInDirection(Protocol::direction direction){
    _action = Protocol::action::MOVE;
    _direction = direction;
}

void Protocol::serialize(){
    _action = (Protocol::action)htons(_action);
    id = htons(id);
    _direction = (Protocol::direction)htons(_direction);
    damage = htons(damage);
    _game_id = htons(_game_id);
    _float_aux = htonl(_float_aux);
}
void Protocol::unSerialize(){
    _action = (Protocol::action)ntohs(_action);
    id = ntohs(id);
    _direction = (Protocol::direction)ntohs(_direction);
    damage = ntohs(damage);
    _game_id = ntohs(_game_id);
    _float_aux = ntohl(_float_aux);
}

void Protocol::setAction(Protocol::action action){
    _action = action;
}

Protocol::~Protocol(){
}
