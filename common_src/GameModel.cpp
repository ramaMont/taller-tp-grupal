#include "GameModel.h"

GameModel::GameModel(int map_id, int game_id):
        Thread(), map(map_id), game_id(game_id){
    initDirections();
} 

GameModel::GameModel(Mapa&& map): 
        Thread(), map(std::move(map)) {
    initDirections();
}

GameModel::GameModel(Mapa&& map, std::map<int,Player>&& players): 
        Thread(), map(std::move(map)), players(std::move(players)){
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

void GameModel::updateEvent(){
}
void GameModel::movePlayer(int player_id){
}

void GameModel::shoot(){
}

void GameModel::processMove(Protocol& protocol){
    Player player = players.at(protocol.getId());
    Direccion* dir = directions.at(protocol.getDirection());
    player.mover(dir);
}

void GameModel::push(Protocol protocol){
    operations.push(protocol);
}

void GameModel::addPlayer(Player player){
    players.insert(std::pair<int, Player>(player.getId(), player));
}

void GameModel::addPlayer(int player_id){
    static int pos_x = 2;
    static int pos_y = 2;
    Coordinates initial_position(pos_x, pos_y);
    Coordinates initial_direction(0, 1);
    Player player(initial_position, initial_direction, map, player_id);
    players.insert(std::pair<int, Player>(player_id, player));
    ++pos_x;
    ++pos_y;
}

Player& GameModel::getPlayer(int user_id){
    return players.at(user_id);
}

Mapa& GameModel::getMap(){
    return map;
}

int GameModel::getId(){
    return game_id;
}

GameModel& GameModel::operator=(GameModel&& other){
    if (this == &other){
        return *this;        // other is myself!
    }
    this->map = std::move(other.map);
    this->is_running = true;
    this->players = std::move(other.players);
    this->directions = std::move(other.directions);
    return *this;
}

GameModel::~GameModel(){
    cleanDirections();
}

GameModelClient::GameModelClient(Mapa&& map, std::map<int,Player>&& players):
        GameModel(std::move(map), std::move(players)){
}



void GameModelClient::processProtocol(Protocol& protocol){
    switch (protocol.getAction()){
        case Protocol::action::MOVE:
            processMove(protocol);
            break;
        case Protocol::action::SHOOT:

            break;
        default:
            break;
    }
}

void GameModelClient::run(){
    while (is_running){
        Protocol protocol = operations.pop();
        processProtocol(protocol);
    }
}

void GameModelClient::stop(){
    is_running = false;
}

GameModelClient::~GameModelClient(){
}
