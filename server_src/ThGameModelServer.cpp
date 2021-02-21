#include "ThGameModelServer.h"

#include "ExceptionServer.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#include <string>

ThGameModelServer::ThGameModelServer(ThUserServer& th_user_server,
        std::string map_filename, int game_id, int map_id_checksum, 
        int bots_cty):
            GameModel(game_id), Thread(), map(map_filename),launched(false),
            th_game_events(operations),
            th_bots(this, operations, players, map, bots_cty),
            map_id_checksum(map_id_checksum), _bots_cty(bots_cty),
            rocket_ids(0){
    addThSender(th_user_server.getSender());
    th_user_server.setGameModel(this);
    addPlayer(th_user_server.getId());
    th_bots.addBots();
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
            break;
        case Protocol::action::DIE:
            processDie(protocol);
            echoProtocol(protocol);
            break;
        case Protocol::action::OPEN:
            processOpen(protocol);
            showPlayersInfo();
            break;
        case Protocol::action::OPENING:
            processOpening(protocol);
            break;
        case Protocol::action::CLOSE:
            processClose(protocol);
            break;
        case Protocol::action::ADDPOINTS:
            sendPlayerProtocol(protocol);
            break;
        case Protocol::action::UPDATE_HEALTH:
            sendPlayerProtocol(protocol);
            break;
        case Protocol::action::UPDATE_BULLETS:
            sendPlayerProtocol(protocol);
            break;
        case Protocol::action::PICKUP:
            echoProtocol(protocol);
            break;
        case Protocol::action::THROW:
            echoProtocol(protocol);
            break;
        case Protocol::action::SWITCH_GUN:
            processGunSwitch(protocol);
            break;
        case Protocol::action::MOVE_ROCKET:
            processMoveRocket(protocol);
            break;
        case Protocol::action::KEY:
            echoProtocol(protocol);
            break;
        case Protocol::action::ENDGAME:
            endGame();
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

void ThGameModelServer::sendPlayerProtocol(Protocol& protocol){
    if (users_sender.count(protocol.getId()) == 0)
        return;
    ThSender* th_user_sender = users_sender.at(protocol.getId());
    th_user_sender->push(protocol);
}

void ThGameModelServer::processShoot(Protocol protocol){
    Player* player = players.at(protocol.getId());
    bool shooted = player->shoot(players);
    if (!shooted) {
        Rocket* rocket = new Rocket(player->get_coordinates(),
            player->get_direction(), player, players, *this, rocket_ids);
        if (!rocket->hasExploded()){
            Event *event = new RocketEvent(rocket);
            th_game_events.add(event);
            rockets[rocket_ids] = rocket;
        }
        rocket_ids ++;
    }
}

void ThGameModelServer::processShooted(Protocol protocol){
    if (users_sender.count(protocol.getId()) == 0)
        return;
    auto th_user_sender = users_sender.at(protocol.getId());
    th_user_sender->push(protocol);
}

void ThGameModelServer::processResurrect(Protocol& protocol){
    Player* player = players.at(protocol.getId());
    Coordinates res_coords = player->revive();
    protocol.setPosition(res_coords.x, res_coords.y);
    echoProtocol(protocol);
}

bool someoneWon(std::map<int, Player*>& players){
    bool winner = false;
    for (auto it = players.begin(); it != players.end(); ++it){
        if (it->second->isAlive()){
            if (winner)
                return false;
            winner = true;
        }
    }
    return true;
}

void ThGameModelServer::processDie(Protocol protocol){
    Player* player = players.at(protocol.getId());
    player->die();
    if (someoneWon(players)){
        endGame(true);
    }
}

void ThGameModelServer::processOpen(Protocol& protocol){
    Player* player = players.at(protocol.getId());
    OpenEvent event(player, map, th_game_events);
    event.process(*this);
}

void ThGameModelServer::processOpening(Protocol& protocol){
    Coordinates pos(protocol.getPosition());
    Door* door = map.getDoor(pos);
    Event* doorE = new DoorEvent(door);
    th_game_events.add(doorE);
    // Cambio la accion del protocolo ya que el mismo contiene toda
    // la informacion necesaria para que el cliente abra la puerta.
    protocol.setAction(Protocol::action::OPEN);
    echoProtocol(protocol);
}

void ThGameModelServer::processClose(Protocol& protocol){
    Coordinates pos(protocol.getPosition());
    if (!map.playerIn(pos)){
        Door* door = static_cast<Door*>(map.getPosicionableIn(pos));
        door->close();
        echoProtocol(protocol);
    } else {
        Door* door = map.getDoor(pos);
        Event* doorE = new DoorEvent(door);
        th_game_events.add(doorE);
    }
}

void ThGameModelServer::processGunSwitch(Protocol& protocol){
    Player* player = players.at(protocol.getId());
    int old_gun = player->actualGun();
    player->switchGun(protocol.getDamage());
    int new_gun = player->actualGun();
    if (new_gun != old_gun)
        echoProtocol(protocol);
}

void ThGameModelServer::processMoveRocket(Protocol& protocol){
    int rocket_id = protocol.getRocketId();
    Rocket* rocket = rockets[rocket_id];
    bool exploded = rocket->move();
    if (exploded)
        rockets.erase(rocket_id);
    /*Coordinates pos(protocol.getPosition());
    try {
        Rocket* rocket = static_cast<Rocket*>(map.getPosicionableIn(pos));
        rocket->move();
    } catch(...) {}*/
}

void ThGameModelServer::run(){
    launched = true;
    Protocol protocol;
    protocol.setAction(Protocol::action::BEGIN);
    echoProtocol(protocol);
    th_game_events.start();
    th_bots.start();
    Event* event = new FinishGameEvent();
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
    map.removePosicionable(coordenadas);
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

int ThGameModelServer::getBotsCty(){
    return _bots_cty;
}

void ThGameModelServer::showPlayersInfo(){
    for (auto& it : players){
        auto player = it.second;
        std::cout << "Jugador:   " << player->getId() << std::endl;
        std::cout << "Posicion:  X: " << player->get_position().x <<
            " Y: " << player->get_position().y  << std::endl;
        std::cout << "Direccion: X: " << player->get_direction().x <<
             " Y: " << player->get_direction().y << std::endl;
        std::cout << "\n-------------------------------------\n";
    }
}

void ThGameModelServer::processTopFiveEnd(){
    std::vector<std::pair<int,int>> ordered_players_kills;
    std::vector<std::pair<int,int>> ordered_players_points;
    std::vector<std::pair<int,int>> ordered_players_bullets;
    for (auto& player: players){
        int player_id = player.second->getId();
        int player_kills = player.second->getKilledEnemies();
        int player_points = player.second->getScore();
        int player_bullets = player.second->getFiredBullets();
        ordered_players_kills.push_back(std::pair<int, int>(player_kills,
            player_id));
        ordered_players_points.push_back(std::pair<int, int>(player_points,
            player_id));
        ordered_players_bullets.push_back(std::pair<int, int>(player_bullets,
            player_id));
    }
    // Ordeno los vectores de menor a mayor
    std::sort(ordered_players_kills.begin(), ordered_players_kills.end());
    std::sort(ordered_players_points.begin(), ordered_players_points.end());
    std::sort(ordered_players_bullets.begin(), ordered_players_bullets.end());
    // Reordeno y me quedo con el top 5
    convertToTopFive(ordered_players_kills);
    convertToTopFive(ordered_players_points);
    convertToTopFive(ordered_players_bullets);
    sendTopFiveToPlayers(ordered_players_kills, ordered_players_points, 
        ordered_players_bullets);
}

void ThGameModelServer::convertToTopFive(std::vector<std::pair<int,int>>& 
        perks_vector){
    int vector_size = 0;
    std::vector<std::pair<int,int>> aux_vect;
    for (auto it = perks_vector.end() - 1; it != perks_vector.begin() - 1; 
            --it){
        if (vector_size >= 5)
            break;
        aux_vect.push_back(*it);
        ++vector_size;
    }
    perks_vector.swap(aux_vect);
}

void ThGameModelServer::sendTopFiveToPlayers(
        const std::vector<std::pair<int,int>>& ordered_players_kills,
        const std::vector<std::pair<int,int>>& ordered_players_points,
        const std::vector<std::pair<int,int>>& ordered_players_bullets){
    //explicit Protocol(int user_id, int danio, Protocol::action action);
    for (auto& kils : ordered_players_kills){
        Protocol protocol(kils.second, kils.first, 
            Protocol::action::END_GAME_KILLS);
        echoProtocol(protocol);
    }

    for (auto& points : ordered_players_points){
        Protocol protocol(points.second, points.first, 
            Protocol::action::END_GAME_POINTS);
        echoProtocol(protocol);
    }

    for (auto& bullets : ordered_players_bullets){
        Protocol protocol(bullets.second, bullets.first, 
            Protocol::action::END_GAME_BULLETS);
        echoProtocol(protocol);
    }
}

void ThGameModelServer::processWinnerEnd(){
    int winner_id;
    for (auto& player :players)
        if (player.second->isAlive())
            winner_id =  player.second->getId();
    Protocol protocol(winner_id);
    protocol.setAction(Protocol::action::WINNER);
    echoProtocol(protocol);
}

void ThGameModelServer::endGame(bool isAWinner){
    Protocol protocol;
    protocol.setAction(Protocol::action::ENDGAME);
    echoProtocol(protocol);
    th_bots.stop();
    if (isAWinner){
        processWinnerEnd();
    }
    processTopFiveEnd();
    Protocol protocol_end;
    protocol_end.setAction(Protocol::action::ENDGAME);
    echoProtocol(protocol_end);
}

void ThGameModelServer::processMove(Protocol& protocol){
    Player* player = players.at(protocol.getId());
    Direction* dir = directions.at(protocol.getDirection());
    player->mover(dir);
}

void ThGameModelServer::push(Protocol protocol){
    operations.push(protocol);
}

void ThGameModelServer::addPlayer(int player_id){
    Player* player = new Player(map, player_id, operations);
    players.insert(std::pair<int, Player*>(player_id, player));
    id_insertion_order.push_back(player_id);
}

Player& ThGameModelServer::getPlayer(int user_id){
    return *players.at(user_id);
}

ServerMap& ThGameModelServer::getMap(){
    return map;
}

int ThGameModelServer::getId(){
    return game_id;
}

std::vector<int>& ThGameModelServer::getIdsVector(){
    return id_insertion_order;
}

ThGameModelServer::~ThGameModelServer(){
    // Todos los jugadores son limpiados en la funcion 
    // removePlayer la cual es llamada cada vez que un jugador
    // se desconecta o se frena la ejecucion de un ThUserServer
    if (launched){
        th_game_events.stop();
        th_game_events.join();
        th_bots.stop();
        th_bots.join();
    }
    for (auto& rocket : rockets){
        delete rocket.second;
    }
}
