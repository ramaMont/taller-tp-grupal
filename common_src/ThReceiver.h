#ifndef __TH_RECEIVER__
#define __TH_RECEIVER__

#include "Thread.h"
#include <queue>
#include "Protocol.h"
#include "Socket.h"
class ThUser;
#include "ThUser.h"

class ThReceiver :  public Thread{
private:
    std::queue<Protocol> operations;
    Socket* socket;
    ThUser* _th_user;
public:
    explicit ThReceiver(Socket *socket);
    virtual void run() override;
    void push(Protocol protocol);
    virtual void stop();
    void setThUser(ThUser* th_user);
    void processReception(Protocol& protocol);
    ~ThReceiver();
};

#endif
