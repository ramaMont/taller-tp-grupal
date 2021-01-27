#include "GameModel.h"

#include <vector>
#include <utility>

GameModel::GameModel(std::string map_filename, int game_id):
        Thread(), map(map_filename), operations(), game_id(game_id){
    initDirections();
} 

/* 
Inicializo el diccionario directions para acceder a cada direccion 
en tiempo O(1)
 */
void GameModel::initDirections(){
    DirAdelante* forward = new DirAdelante();
    DirAtras* backward = new DirAtras();
    DirIzquierda* left = new DirIzquierda();
    DirDerecha* right = new DirDerecha();
    DirRotIzquierda* rotLeft = new DirRotIzquierda();
    DirRotDerecha* rotRight = new DirRotDerecha();
    directions[Protocol::direction::FORWARD] = forward;
    directions[Protocol::direction::BACKWARD] = backward;
    directions[Protocol::direction::LEFT] = left;
    directions[Protocol::direction::RIGHT] = right;
    directions[Protocol::direction::ROTATE_LEFT] = rotLeft;
    directions[Protocol::direction::ROTATE_RIGHT] = rotRight;
}

void GameModel::cleanDirections(){
    for (auto it = directions.begin(); it != directions.end(); ++it){
        Direccion* dir = it->second;
        delete(dir);
    }
}

void GameModel::processMove(Protocol& protocol){
    Player* player = players.at(protocol.getId());
    Direccion* dir = directions.at(protocol.getDirection());
    player->mover(dir);
}

void GameModel::push(Protocol protocol){
    std::lock_guard<std::mutex> lck(m);
    operations.push(protocol);
}

void GameModel::addPlayer(int player_id){
    try{
        Player* player = new Player(map, player_id, operations);
        players.insert(std::pair<int, Player*>(player_id, player));
        id_insertion_order.push_back(player_id);
    } catch(...){
    }
}

Player& GameModel::getPlayer(int user_id){
    return *players.at(user_id);
}

Mapa& GameModel::getMap(){
    return map;
}

int GameModel::getId(){
    return game_id;
}

std::vector<int>& GameModel::getIdsVector(){
    return id_insertion_order;
}

GameModel& GameModel::operator=(GameModel&& other){
    if (this == &other){
        return *this;        // other is myself!
    }
    this->map = std::move(other.map);
    this->is_running = true;
    this->players = std::move(other.players);
    this->directions = std::move(other.directions);
    this->game_id = std::move(other.game_id);
    return *this;
}

GameModel::~GameModel(){
    cleanDirections();
}
