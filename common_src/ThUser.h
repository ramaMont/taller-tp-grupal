#ifndef __TH_USER__
#define __TH_USER__

#include <Thread.h>
#include "Protocol.h"
#include "BlockingQueue.h"
#include "ThSender.h"
class ThReceiver;
#include "ThReceiver.h"

class ThUser : public Thread{
protected:
    BlockingQueue<Protocol> operations;
    int user_id;

public:
    explicit ThUser(int user_id);
    virtual void run() override;
    void push(Protocol protocol);
    int getId();
    virtual void stop() override;
    ~ThUser();
};

#endif
