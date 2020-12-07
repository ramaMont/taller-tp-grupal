#ifndef __TH_USER__
#define __TH_USER__

#include "Protocol.h"
#include <queue>
#include "ThSender.h"
class ThReceiver;
#include "ThReceiver.h"

class ThUser{
protected:
    std::queue<Protocol> operations;
    int user_id;
    ThReceiver& th_receiver;
    ThSender& th_sender;

public:
    explicit ThUser(int user_id, ThReceiver& th_receiver, ThSender& th_sender);
    virtual void run();
    void push(Protocol protocol);
    int getId();
    ~ThUser();
};

class ThUserClient : public ThUser{
public:
    explicit ThUserClient(int user_id, ThReceiver& th_receiver, ThSender& th_sender);
    virtual void run() override;
    ~ThUserClient();
};

class ThUserServer : public ThUser{
public:
    explicit ThUserServer(int user_id, ThReceiver& th_receiver, ThSender& th_sender);
    virtual void run() override;
    ~ThUserServer();
};

#endif
