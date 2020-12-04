#include "Protocol.h"

Protocol::Protocol(){
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
Protocol::~Protocol(){
}