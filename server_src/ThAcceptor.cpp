#include "ThAcceptor.h"
#include <vector>
#include <ThReceiver.h>
#include <ThSender.h>

#include <string>

void ThAcceptor::cleanZombies(){
    std::vector<ThUserServer*> activeThreads;
    for (size_t i = 0; i < user_peers.size(); i++){
        if (user_peers[i]->isDone()){
            user_peers[i]->join();
            delete user_peers[i];
        } else {
            activeThreads.push_back(user_peers[i]);
        }
    }
    user_peers.swap(activeThreads);
}

ThAcceptor::ThAcceptor(const std::string& port, GamesAdmin& games_admin):
    Thread(), socket_aceptador(port), games_admin(games_admin){
}
void ThAcceptor::run(){
    try{
        int current_id = 0;
        while (is_running){
            Socket socket_peer = socket_aceptador.acceptClient();
            cleanZombies();
            ThUserServer* th_user_peer = 
                new ThUserServer(current_id, std::move(socket_peer),
                games_admin);
            user_peers.push_back(th_user_peer);
            th_user_peer->start();
            ++current_id;
        }
    } catch(...){
        is_running = false;
    }
}
void ThAcceptor::stop(){
    is_running = false;
    socket_aceptador.shutdown();
    socket_aceptador.close();
}
ThAcceptor::~ThAcceptor(){
    for (size_t i = 0; i < user_peers.size(); i++){
        user_peers[i]->stop();
        user_peers[i]->join();
        delete(user_peers[i]);
    }
}
