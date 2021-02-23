#ifndef __TH_RECEIVER__
#define __TH_RECEIVER__

#include "Thread.h"
#include "Protocol.h"
#include "Socket.h"

class ThReceiver :  public Thread{
protected:
    Socket* socket;

public:
    explicit ThReceiver(Socket *socket);
    virtual void run() override = 0;
    virtual void stop() override;
    virtual void processReception(Protocol& protocol) = 0;
    virtual ~ThReceiver();
};

#endif
