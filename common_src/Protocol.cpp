#include "Protocol.h"
#include<arpa/inet.h>
#include <tuple>

Protocol::Protocol():
    _action(Protocol::action::NONE), _id_botCty(0), 
    _direction(Protocol::direction::STAY), _damage_mapId_life(0), _game_id_posX(0), 
    _float_aux(0){
}

Protocol::Protocol(int _id_botCty):
    _action(Protocol::action::NONE), _id_botCty(_id_botCty), 
    _direction(Protocol::direction::STAY), _damage_mapId_life(0), _game_id_posX(0), 
    _float_aux(0){
}

Protocol::Protocol(int user_id, int map_id):
    _action(Protocol::action::NONE), _id_botCty(user_id), 
    _direction(Protocol::direction::STAY), _damage_mapId_life(map_id), _game_id_posX(0), 
    _float_aux(0){
}

Protocol::Protocol(int user_id, int danio, Protocol::action action):
    _action(action), _id_botCty(user_id), 
    _direction(Protocol::direction::STAY), _damage_mapId_life(danio), _game_id_posX(0), 
    _float_aux(0){
}

Protocol::Protocol(int user_id, int map_id, int game_id):
    _action(Protocol::action::NONE), _id_botCty(user_id), 
    _direction(Protocol::direction::STAY), _damage_mapId_life(map_id), _game_id_posX(game_id), 
    _float_aux(0){
}

Protocol::Protocol(int _id_botCty, Protocol::direction direction):
        _action(Protocol::action::MOVE), _id_botCty(_id_botCty), _direction(direction),
        _damage_mapId_life(0), _game_id_posX(0), _float_aux(0){
}

Protocol::Protocol(int config_number, float config_value):
        _action(Protocol::action::CONFIG), _id_botCty(config_number),
        _direction(Protocol::direction::STAY), _damage_mapId_life(0),
        _game_id_posX(0), _float_aux(config_value){
}

Protocol::Protocol(Protocol::action action, int user_id, 
            Protocol::direction direction, int map_id, int pos_x, int pos_y):
        _action(action), _id_botCty(user_id),
        _direction(direction), _damage_mapId_life(map_id),
        _game_id_posX(pos_x), _float_aux((float)pos_y){
}

Protocol::Protocol(Protocol::action action, int player_id, int rocket_id):
        _action(action), _id_botCty(player_id), _direction(Protocol::direction::STAY),\
        _damage_mapId_life(0), _game_id_posX(rocket_id), _float_aux(0){
}

Protocol::action Protocol::getAction(){
    return _action;
}
int Protocol::getId(){
    return _id_botCty;
}
int Protocol::getMapId(){
    return _damage_mapId_life;
}

int Protocol::getUserId(){
    return _id_botCty;
}
int Protocol::getGameId(){
    return _game_id_posX;
}
int Protocol::getDamage(){
    return _damage_mapId_life;
}

Protocol::direction Protocol::getDirection(){
    return _direction;
}

int Protocol::getConfId(){
    return _id_botCty;
}

int Protocol::getBotsCty(){
    return _id_botCty;
}

float Protocol::getConfiguration(){
    return _float_aux;
}

int Protocol::getRocketId(){
    return _game_id_posX;
}

std::tuple<int, int> Protocol::getPosition() const{
    int pos_x = _game_id_posX;
    int pos_y = (int)_float_aux;
    return std::make_tuple(pos_x, pos_y);
}

void Protocol::moveInDirection(Protocol::direction direction){
    _action = Protocol::action::MOVE;
    _direction = direction;
}

Protocol::NetworkProtocol Protocol::serialize() const{
    Protocol::NetworkProtocol sending_protocol;
    sending_protocol._action = (Protocol::action)htons(_action);
    sending_protocol._id_botCty = htons(_id_botCty);
    sending_protocol._direction = (Protocol::direction)htons(_direction);
    sending_protocol._damage_mapId_life = htons(_damage_mapId_life);
    sending_protocol._game_id_posX = htons(_game_id_posX);
    sending_protocol._float_aux = htonl(_float_aux);
    return sending_protocol;
}

void Protocol::unSerialize(const Protocol::NetworkProtocol& received_protocol){
    _action = (Protocol::action)ntohs(received_protocol._action);
    _id_botCty = ntohs(received_protocol._id_botCty);
    _direction = (Protocol::direction)ntohs(received_protocol._direction);
    _damage_mapId_life = ntohs(received_protocol._damage_mapId_life);
    _game_id_posX = ntohs(received_protocol._game_id_posX);
    _float_aux = ntohl(received_protocol._float_aux);
}

void Protocol::setAction(Protocol::action action){
    _action = action;
}

void Protocol::setDamage(int danio){
    _damage_mapId_life = danio;
}

void Protocol::setPosition(int pos_x, int pos_y){
    _game_id_posX = pos_x;
    _float_aux = (float)pos_y;
}

Protocol::~Protocol(){
}
