#ifndef __TH_SENDER__
#define __TH_SENDER__

#include <queue>
#include "Protocol.h"
class ThReceiver;
#include "ThReceiver.h"

class ThSender{
private:
    std::queue<Protocol> operations;
    ThReceiver& other_receiver;
    int id_user;
public:
    explicit ThSender(ThReceiver& other_receiver, int id_user);
    void run();
    int getId();
    void push(Protocol protocol);
    ~ThSender();
};

#endif
