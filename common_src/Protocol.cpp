#include "Protocol.h"

Protocol::Protocol(int id):id(id){
}

Protocol::Protocol(int id, const enum direction):
        id(id){
//    this->direction = direction;
}
Protocol::action Protocol::getAction(){
    return _action;
}
int Protocol::getId(){
    return id;
}
Protocol::direction Protocol::getDirection(){
    return _direction;
}
void Protocol::moveInDirection(Protocol::direction direction){
    _action = Protocol::action::MOVE;
    _direction = direction;
}

Protocol::~Protocol(){
}