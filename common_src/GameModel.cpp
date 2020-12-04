#include "GameModel.h"

GameModel::GameModel(Mapa&& map): 
        map(std::move(map)), keep_running(true){
    initDirections();
}

GameModel::GameModel(Mapa&& map, std::map<int,Player *>&& players, std::map<int,ThSender *>&& users_sender): 
        map(std::move(map)), keep_running(true), players(players), users_sender(users_sender){
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
    directions[FORWARD] = forward;
    directions[BACKWARD] = backward;
    directions[LEFT] = left;
    directions[RIGHT] = right;
    directions[ROTATE_LEFT] = rotLeft;
    directions[ROTATE_RIGHT] = rotRight;
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

void GameModel::processProtocol(Protocol& protocol){
    switch (protocol.getAction()){
        case MOVE:
            processMove(protocol);
            echoProtocol(protocol);
            break;
        case SHOOT:

            break;
        default:
            break;
    }
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
void GameModel::addThSender(ThSender* th_sender){
    users_sender.insert(std::pair<int, ThSender*>(th_sender->getId(), th_sender));
}

void GameModel::echoProtocol(Protocol protocol){
    std::map<int, ThSender *>::iterator it = users_sender.begin();
    while (it != users_sender.end()){
        ThSender* user_sender = it->second;
        user_sender->push(protocol);
        it++;
    }
}

GameModel& GameModel::operator=(GameModel&& other){
    if (this == &other){
        return *this;        // other is myself!
    }
    this->map = std::move(other.map);
    this->keep_running = true;
    this->players = std::move(other.players);
    this->users_sender = std::move(other.users_sender);
    this->directions = std::move(other.directions);
    return *this;
}

GameModel::~GameModel(){
}
