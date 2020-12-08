#include "ThAcceptor.h"
#include <vector>

void ThAcceptor::cleanZombies(){
    std::vector<Thread*> activeThreads;
    for (size_t i = 0; i < peers.size(); i++){
        if (!peers[i]->isDone()){
            peers[i]->join();
            delete peers[i];
        } else {
            activeThreads.push_back(peers[i]);
        }
    }
    peers.swap(activeThreads);
}

ThAcceptor::ThAcceptor(const std::string& port):
    Thread(), socket_aceptador(port){
}
void ThAcceptor::run(){
    int current_id = 0;
    while (is_running){
        Socket socket_receptor = socket_aceptador.acceptClient();
        cleanZombies();
        Protocol protocol(current_id);
        protocol.setAction(Protocol::action::SET_ID);
        socket_receptor.send(protocol, sizeof(Protocol));
        ++current_id;
    }
}
void ThAcceptor::stop(){
    is_running = false;
}
ThAcceptor::~ThAcceptor(){
}

