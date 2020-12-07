#ifndef __TH_RECEIVER__
#define __TH_RECEIVER__

#include "Thread.h"
#include <queue>
#include "Protocol.h"
#include "Socket.h"

class ThReceiver :  public Thread{
private:
    std::queue<Protocol> operations;
    Socket* socket;
public:
    explicit ThReceiver(Socket *socket);
    virtual void run() override;
    void push(Protocol protocol);
    virtual void stop();
    ~ThReceiver();
};

#endif
