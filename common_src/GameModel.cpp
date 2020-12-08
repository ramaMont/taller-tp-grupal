#include "GameModel.h"

// GameModel::GameModel(Mapa& map): 
//         map(map), keep_running(true){
//     initDirections();
// }

GameModel::GameModel(Mapa&& map, std::map<int,Player *>&& players): 
        map(std::move(map)), keep_running(true), players(std::move(players)){
    // Inicializo el diccionario directions para acceder a cada direccion 
    // en tiempo O(1)
    // verificar si esto anda o si los punteros se pierden cuando finaliza
    // el constructor.
    initDirections();
}

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

void GameModel::run(){
    if (!operations.empty()){
        Protocol protocolo = operations.front();
        operations.pop();
        processProtocol(protocolo);
    }
}


void GameModel::updateEvent(){
}
void GameModel::movePlayer(int player_id){
}

void GameModel::shoot(){
}

void GameModel::processMove(Protocol& protocol){
    Player* player = players.at(protocol.getId());
    Direccion* dir = directions.at(protocol.getDirection());
    player->mover(dir);
}

void GameModel::push(Protocol protocol){
    operations.push(protocol);
}

void GameModel::addPlayer(Player* player){
    players.insert(std::pair<int, Player*>(player->getId(), player));
}

GameModel& GameModel::operator=(GameModel&& other){
    if (this == &other){
        return *this;        // other is myself!
    }
    this->map = std::move(other.map);
    this->keep_running = true;
    this->players = std::move(other.players);
    this->directions = std::move(other.directions);
    return *this;
}

GameModel::~GameModel(){
    cleanDirections();
}

GameModelServer::GameModelServer(Mapa&& map, std::map<int,Player *>&& players,
        std::map<int,ThSender *>& users_sender):
        GameModel(std::move(map), std::move(players)),
        users_sender(users_sender){
}

GameModelClient::GameModelClient(Mapa&& map, std::map<int,Player *>&& players):
        GameModel(std::move(map), std::move(players)){
}

void GameModelServer::processProtocol(Protocol& protocol){
    switch (protocol.getAction()){
        case Protocol::action::MOVE:
            processMove(protocol);
            echoProtocol(protocol);
            break;
        case Protocol::action::SHOOT:

            break;
        default:
            break;
    }
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

void GameModelServer::addThSender(ThSender* th_sender){
    users_sender.insert(std::pair<int, ThSender*>(th_sender->getId(), th_sender));
}

void GameModelServer::echoProtocol(Protocol protocol){
    std::map<int, ThSender *>::iterator it = users_sender.begin();
    while (it != users_sender.end()){
        ThSender* user_sender = it->second;
        user_sender->push(protocol);
        it++;
    }
}

GameModelServer::~GameModelServer(){
}

GameModelClient::~GameModelClient(){
}
