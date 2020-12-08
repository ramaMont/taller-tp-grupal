#ifndef __TH_SENDER__
#define __TH_SENDER__

#include "Thread.h"
#include "BlockingQueue.h"
#include "Protocol.h"
#include "Socket.h"

class ThSender : public Thread{
private:
    BlockingQueue<Protocol> operations;
    int id_user;
    Socket* socket;
public:
    explicit ThSender(int id_user, Socket* socket);
    virtual void run() override;
    int getId();
    void push(Protocol protocol);
    virtual void stop() override;
    ~ThSender();
};

#endif
