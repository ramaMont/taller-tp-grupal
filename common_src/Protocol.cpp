#include "Protocol.h"
#include<arpa/inet.h>

Protocol::Protocol():
    _action(Protocol::action::NONE), id(0), 
    _direction(Protocol::direction::STAY), damage(0), _game_id(0){
}

Protocol::Protocol(int id):
    _action(Protocol::action::NONE), id(id), 
    _direction(Protocol::direction::STAY), damage(0), _game_id(0){
}

Protocol::Protocol(int user_id, int map_id):
    _action(Protocol::action::NONE), id(user_id), 
    _direction(Protocol::direction::STAY), damage(map_id), _game_id(0){
}

Protocol::Protocol(int user_id, int map_id, int game_id):
    _action(Protocol::action::NONE), id(user_id), 
    _direction(Protocol::direction::STAY), damage(map_id), _game_id(game_id){
}

Protocol::Protocol(int id, Protocol::direction direction):
        _action(Protocol::action::MOVE), id(id), _direction(direction),
        damage(0), _game_id(0){
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

Protocol::direction Protocol::getDirection(){
    return _direction;
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
}
void Protocol::unSerialize(){
    _action = (Protocol::action)ntohs(_action);
    id = ntohs(id);
    _direction = (Protocol::direction)ntohs(_direction);
    damage = ntohs(damage);
    _game_id = ntohs(_game_id);
}

void Protocol::setAction(Protocol::action action){
    _action = action;
}

Protocol::~Protocol(){
}