#ifndef __TH_USER__
#define __TH_USER__

#include "Protocol.h"
#include <queue>
#include "ThSender.h"
class ThReceiver;
#include "ThReceiver.h"

class ThUser{
private:
    std::queue<Protocol> operations;
    int user_id;
    ThReceiver& th_receiver;
    ThSender& th_sender;

public:
    explicit ThUser(int user_id, ThReceiver& th_receiver, ThSender& th_sender);
    void run();
    void push(Protocol protocol);
    int getId();
    ~ThUser();
};

// class ThUserClient : public ThUser{
// public:
//     explicit ThUserClient(GameModel& game_model, int id);
//     virtual void run() override;
//     void push(Protocol protocol);
//     int getId();
//     ~ThUserClient();
// };

// class ThUserServer : public ThUser{
// public:
//     explicit ThUserServer(GameModel& game_model, int id);
//     virtual void run() override;
//     void push(Protocol protocol);
//     int getId();
//     ~ThUserServer();
// };

#endif
