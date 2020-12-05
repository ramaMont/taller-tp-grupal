#include "Protocol.h"

Protocol::Protocol(int id):id(id){
}
enum action Protocol::getAction(){
    return action;
}
int Protocol::getId(){
    return id;
}
enum direction Protocol::getDirection(){
    return direction;
}
void Protocol::setDirection(enum direction){
    direction = direction;
}

Protocol::~Protocol(){
}