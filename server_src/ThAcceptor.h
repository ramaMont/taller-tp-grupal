#ifndef __TH_ACCEPTOR__
#define __TH_ACCEPTOR__

#include <Thread.h>
#include <Socket.h>
#include "ThUserServer.h"
#include "GamesAdmin.h"

#include <vector>
#include <string>

class ThAcceptor : public Thread{
    std::vector<ThUserServer*> user_peers;
    SocketServer socket_aceptador;
    GamesAdmin& games_admin;
    void cleanZombies();
    void sendConfiguration(Socket& socket_peer);
public:
    explicit ThAcceptor(const std::string& port, GamesAdmin& games_admin);
    virtual void run() override;
    virtual void stop() override;
    ~ThAcceptor();
};

#endif
