#include "ThGameModelServer.h"

#include <vector>
#include <map>
#include <utility>
#include "ExceptionServer.h"

ThGameModelServer::ThGameModelServer(ThUserServer& th_user_server,
        std::string map_filename, int game_id, int map_id_checksum):
    GameModel(map_filename, game_id), launched(false),
    th_game_events(operations),
    th_bots(this, operations, players, map, 0),
    map_id_checksum(map_id_checksum){
    addThSender(th_user_server.getSender());
    addPlayer(th_user_server.getId());
    th_user_server.setGameModel(this);
}

void ThGameModelServer::processProtocol(Protocol& protocol){
    switch (protocol.getAction()){
        case Protocol::action::MOVE:
            processMove(protocol);
            echoProtocol(protocol);
            break;
        case Protocol::action::SHOOT:
            processShoot(protocol);
            echoProtocol(protocol);
            break;
        case Protocol::action::SHOOTED:
            processShooted(protocol);
            break;
        case Protocol::action::RESURRECT:
            processResurrect(protocol);
            echoProtocol(protocol);
            break;
        case Protocol::action::DIE:
            processDie(protocol);
            echoProtocol(protocol);
            break;
        case Protocol::action::OPEN:
            processOpen(protocol);
            break;
        default:
            break;
    }
}

void ThGameModelServer::addThSender(ThSender* th_sender){
    users_sender.insert(std::pair<int, ThSender*>(th_sender->getId(),
        th_sender));
}

void ThGameModelServer::echoProtocol(Protocol protocol){
    std::map<int, ThSender *>::iterator it = users_sender.begin();
    while (it != users_sender.end()){
        ThSender* user_sender = it->second;
        user_sender->push(protocol);
        ++it;
    }
}

void ThGameModelServer::processShoot(Protocol protocol){
    Player* player = players.at(protocol.getId());
    try {
        player->disparar(players);
    } catch(const RocketException &e) {
        Event *event = new RocketEvent(player->get_coordinates(),
            player->get_direction(), player, players);
        th_game_events.add(event);
    } catch(...) {}
}

void ThGameModelServer::processShooted(Protocol protocol){
    auto th_user_sender = users_sender.at(protocol.getId());
    th_user_sender->push(protocol);
}

void ThGameModelServer::processResurrect(Protocol protocol){
    Player* player = players.at(protocol.getId());
    player->revivir();
}

void ThGameModelServer::processDie(Protocol protocol){
    Player* player = players.at(protocol.getId());
    player->morir();
}
/*
void ThGameModelServer::processOpen(Protocol& protocol){
    // TODO: Calcular que puerta abrir y eso.
    // Modificar al protocolo para que al momento de enviarselo nuevamente.
    // al cliente le diga la posicion de la puerta a abrir.
    // Por ahora:
    echoProtocol(protocol);
}
*/

void ThGameModelServer::processOpen(Protocol& protocol){
    Player* player = players.at(protocol.getId());
    OpenEvent event(player, map, th_game_events);
    event.process(*this);
}


void ThGameModelServer::run(){
    launched = true;
    Protocol protocol;
    protocol.setAction(Protocol::action::BEGIN);
    echoProtocol(protocol);
    th_game_events.start();
    th_bots.start();
    Event* event = new FinishGameEvent(players);
    th_game_events.add(event);
    try{
        while (is_running){
            protocol = operations.pop();
            processProtocol(protocol);
        }
    } catch(...){
        is_running = false;
    }
}

void ThGameModelServer::removePlayer(int user_id){
    auto player = players.at(user_id);
    auto coordenadas = player->get_coordinates();
    delete(player);
    players.erase(user_id);
    users_sender.erase(user_id);
    Protocol protocol(user_id);
    map.sacarPosicionable(coordenadas);
    protocol.setAction(Protocol::action::REMOVE);
    echoProtocol(protocol);
}

void ThGameModelServer::stop(){
    is_running = false;
    operations.stop();
    th_game_events.stop();
    th_bots.stop();
}

bool ThGameModelServer::isDone(){
    if (players.size() == 0)
        return true;
    return !is_running;
}

bool ThGameModelServer::wasLaunched(){
    return launched;
}

int ThGameModelServer::getMapIdChecksum(){
    return map_id_checksum;
}

ThGameModelServer::~ThGameModelServer(){
    // Todos los jugadores son limpiados en la funcion 
    // removePlayer la cual es llamada cada vez que un jugador
    // se desconecta o se frena la ejecucion de un ThUserServer
    
    th_game_events.join();
    th_bots.join();
}
