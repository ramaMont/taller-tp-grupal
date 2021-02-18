#include "Protocol.h"
#include<arpa/inet.h>
#include <tuple>
#define DECIMALS 100

Protocol::Protocol():
    _action(Protocol::action::NONE), id(0), 
    _direction(Protocol::direction::STAY), damage(0), _game_id(0), 
    _float_aux(0){
}

Protocol::Protocol(int id):
    _action(Protocol::action::NONE), id(id), 
    _direction(Protocol::direction::STAY), damage(0), _game_id(0), 
    _float_aux(0){
}

Protocol::Protocol(int user_id, int map_id):
    _action(Protocol::action::NONE), id(user_id), 
    _direction(Protocol::direction::STAY), damage(map_id), _game_id(0), 
    _float_aux(0){
}

Protocol::Protocol(int user_id, int danio, Protocol::action action):
    _action(action), id(user_id), 
    _direction(Protocol::direction::STAY), damage(danio), _game_id(0), 
    _float_aux(0){
}

Protocol::Protocol(int user_id, int map_id, int game_id):
    _action(Protocol::action::NONE), id(user_id), 
    _direction(Protocol::direction::STAY), damage(map_id), _game_id(game_id), 
    _float_aux(0){
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

Protocol::Protocol(Protocol::action action, int user_id, 
            Protocol::direction direction, int map_id, int pos_x, int pos_y):
        _action(action), id(user_id),
        _direction(direction), damage(map_id),
        _game_id(pos_x), _float_aux((float)pos_y){
}

Protocol::Protocol(Protocol::action action, int _id, float pos_x, float pos_y):
        _action(action), id(_id), _direction(Protocol::direction::STAY),\
        damage(0){
    _game_id = pos_x * DECIMALS;
    _float_aux = pos_y * DECIMALS;
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

std::tuple<int, int> Protocol::getPosition() const{
    int pos_x = _game_id;
    int pos_y = (int)_float_aux;
    return std::make_tuple(pos_x, pos_y);
}

std::tuple<float, float> Protocol::getFloatPosition() const{
    float pos_x = (float)_game_id / DECIMALS;
    float pos_y = (float)_float_aux / DECIMALS;
    return std::make_tuple(pos_x, pos_y);
}

void Protocol::moveInDirection(Protocol::direction direction){
    _action = Protocol::action::MOVE;
    _direction = direction;
}

Protocol::NetworkProtocol Protocol::serialize() const{
    Protocol::NetworkProtocol sending_protocol;
    sending_protocol._action = (Protocol::action)htons(_action);
    sending_protocol.id = htons(id);
    sending_protocol._direction = (Protocol::direction)htons(_direction);
    sending_protocol.damage = htons(damage);
    sending_protocol._game_id = htons(_game_id);
    sending_protocol._float_aux = htonl(_float_aux);
    return sending_protocol;
}

void Protocol::unSerialize(const Protocol::NetworkProtocol& received_protocol){
    _action = (Protocol::action)ntohs(received_protocol._action);
    id = ntohs(received_protocol.id);
    _direction = (Protocol::direction)ntohs(received_protocol._direction);
    damage = ntohs(received_protocol.damage);
    _game_id = ntohs(received_protocol._game_id);
    _float_aux = ntohl(received_protocol._float_aux);
}

void Protocol::setAction(Protocol::action action){
    _action = action;
}

void Protocol::setDamage(int danio){
    damage = danio;
}

Protocol::~Protocol(){
}
