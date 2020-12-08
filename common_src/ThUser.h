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
    ThReceiver& th_receiver;
    ThSender& th_sender;

public:
    explicit ThUser(int user_id, ThReceiver& th_receiver, ThSender& th_sender);
    virtual void run() override;
    void push(Protocol protocol);
    int getId();
    virtual void stop() override;
    ~ThUser();
};

class ThUserClient : public ThUser{
private:
    void joinOrCreateGame();
    void processReception(Protocol& protocol);
    void createGameModel(int map_id);
    void waitUntilLaunch();
    void play();
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
