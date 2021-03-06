#include "ThUserServer.h"

#include <Protocol.h>
#include <ConfigVariable.h>
#include <MapLoader.h>

#include <iostream>
#include <exception>
#include <vector>

ThUserServer::ThUserServer(int user_id, Socket&& socket_peer,
        GamesAdmin& games_admin):
    Thread(),
    socket_peer(std::move(socket_peer)),
    th_receiver_server(nullptr),
    th_sender(nullptr),
    games_admin(games_admin),
    game_id(-1), user_id(user_id){
}

void ThUserServer::sendConfiguration(){
    for (auto &config : configs){
        Protocol protocol_config(config.first, config.second);
        socket_peer.send(protocol_config);
    }
    Protocol protocol_end;
    protocol_end.setAction(Protocol::action::END);
    socket_peer.send(protocol_end);
}

void ThUserServer::respondSuccess(){
    Protocol protocol;
    protocol.setAction(Protocol::action::OK);
    th_sender->push(protocol);
}

void ThUserServer::respondSuccess(int map_id){
    Protocol protocol(user_id, map_id, game_id);
    protocol.setAction(Protocol::action::OK);
    th_sender->push(protocol);
}

void ThUserServer::respondError(){
    Protocol protocol(user_id);
    protocol.setAction(Protocol::action::ERROR);
    th_sender->push(protocol);
}

void ThUserServer::initCommunication(){
    Protocol protocol(user_id);
    protocol.setAction(Protocol::action::SET_ID);
    socket_peer.send(protocol);
    sendConfiguration();
    th_receiver_server = new ThReceiverServer(&socket_peer);
    th_receiver_server->setThUser(this);
    th_sender = new ThSender(user_id, &socket_peer);
    th_receiver_server->start();
    th_sender->start();
}

void ThUserServer::processReception(Protocol& protocol){
    switch (protocol.getAction()){
        case Protocol::action::CREATE_GAME:{
            try{
                MapLoader mapLoader(protocol.getMapId());
                int bots_cty = protocol.getBotsCty();
                games_admin.createGame(*this, mapLoader.getFileName(),
                    protocol.getMapId(), bots_cty);
                respondSuccess(protocol.getMapId());
                Coordinates player_direction = games_admin.
                    getGame(game_id)->getPlayer(user_id).get_direction();
                Coordinates player_position = games_admin.
                    getGame(game_id)->getPlayer(user_id).get_coordinates();
                Protocol::direction prot_direction = player_direction.
                    cast_to_direction();
                Protocol protocol_response(Protocol::action::CREATE_GAME,
                    user_id, prot_direction, mapLoader.getChecksum(), 
                    player_position.x, player_position.y);      
                th_sender->push(protocol_response);
                sendBotsPositions();
            } catch(...){
                respondError();
            }
            break;
        }
        case Protocol::action::JOIN_GAME:{
            try{
                int game_id = protocol.getId();
                games_admin.joinGame(*this, game_id);
            } catch(...){
                respondError();
            }
            break;
        }
        case Protocol::action::LAUNCH_GAME:{
            int game_id = protocol.getId();
            games_admin.launchGame(game_id);
            respondSuccess();
            break;
        }
        default:
            // Algo salio muy mal.
            std::cout << "Nunca deberia entrar acá\n";
            break;
    }
}

void ThUserServer::run(){
    initCommunication();
    try{
        while (is_running){
            Protocol protocol = operations.pop();
            processReception(protocol);
        }
    } catch(...){
        is_running = false;
    }
    if (game_id != -1)
        games_admin.removePlayer(game_id, user_id);
}

void ThUserServer::stop(){
    is_running = false;
    operations.stop();
}

ThSender* ThUserServer::getSender(){
    return th_sender;
}

void ThUserServer::setGameModel(ThGameModelServer* th_game_model){
    th_receiver_server->setGameModel(th_game_model);
}

void ThUserServer::setGameId(int game_id){
    this->game_id = game_id;
}

void ThUserServer::transmit(std::vector<int>& ids_vector, int map_id_checksum){
    respondSuccess(map_id_checksum);
    for (auto it = ids_vector.begin(); it != ids_vector.end(); ++it){
        Coordinates player_direction = games_admin.
            getGame(game_id)->getPlayer(*it).get_direction();
        Coordinates player_position = games_admin.
            getGame(game_id)->getPlayer(*it).get_coordinates();
        Protocol::direction prot_direction = player_direction.
            cast_to_direction();
        Protocol protocol_response(Protocol::action::ADD_PLAYER,
            *it, prot_direction, map_id_checksum, 
            player_position.x, player_position.y);      
        th_sender->push(protocol_response);
    }
    Protocol protocol;
    protocol.setAction(Protocol::action::END);
    th_sender->push(protocol);
}

void ThUserServer::sendBotsPositions(){
    auto th_game = games_admin.getGame(game_id);
    int bots_cty = th_game->getBotsCty();
    int map_id_checksum = th_game->getMapIdChecksum();
    std::vector<int>& ids_vector = th_game->getIdsVector();
    for (int i = 1; (i - 1) < bots_cty; ++i){
        int bot_id = ids_vector.at(i);
        Coordinates player_direction = th_game->getPlayer(bot_id).
            get_direction();
        Coordinates player_position = th_game->getPlayer(bot_id).
            get_coordinates();
        Protocol::direction prot_direction = player_direction.
            cast_to_direction();
        Protocol protocol_response(Protocol::action::ADD_PLAYER,
            bot_id, prot_direction, map_id_checksum, 
            player_position.x, player_position.y);      
        th_sender->push(protocol_response);
    }
}

void ThUserServer::push(Protocol protocol){
    operations.push(protocol);
}

int ThUserServer::getId(){
    return user_id;
}

ThUserServer::~ThUserServer(){
    socket_peer.shutdown();
    socket_peer.close();
    if (th_receiver_server != nullptr){
        th_receiver_server->stop();
        th_receiver_server->join();
        delete(th_receiver_server);
    }
    if (th_sender != nullptr){
        th_sender->stop();
        th_sender->join();
        delete(th_sender);
    }
}
