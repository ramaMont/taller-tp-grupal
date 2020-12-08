#ifndef __TH_ACCEPTOR__
#define __TH_ACCEPTOR__

#include <Thread.h>
#include <Socket.h>
#include <vector>

class ThAcceptor : public Thread{
    std::vector<Thread*> peers;
    SocketServer socket_aceptador;
    void cleanZombies();
public:
    explicit ThAcceptor(const std::string& port);
    virtual void run() override;
    virtual void stop() override;
    ~ThAcceptor();
};

#endif
