#include "Protocol.h"
#include<arpa/inet.h>

Protocol::Protocol(int id):id(id){
}

Protocol::Protocol(int user_id, int map_id):
    id(user_id), damage(map_id){
}

Protocol::Protocol(int id, Protocol::direction direction):
        _action(Protocol::action::MOVE), id(id), _direction(direction){
}
Protocol::action Protocol::getAction(){
    return _action;
}
int Protocol::getId(){
    return id;
}
int Protocol::getId2(){
    return damage;
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
}
void Protocol::unSerialize(){
    _action = (Protocol::action)ntohs(_action);
    id = ntohs(id);
    _direction = (Protocol::direction)ntohs(_direction);
    damage = ntohs(damage);
}

void Protocol::setAction(Protocol::action action){
    _action = action;
}

Protocol::~Protocol(){
}