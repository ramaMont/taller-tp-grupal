#ifndef __TH_GAME_MODEL_SERVER__
#define __TH_GAME_MODEL_SERVER__

#include <GameModel.h>
class ThUserServer;
#include "ThUserServer.h"

#include <atomic>
#include <map>

class ThGameModelServer : public GameModel{
private:
    std::map<int,ThSender *> users_sender;
    std::atomic<bool> launched;

    void processShoot(Protocol protocol);
    void processShooted(Protocol protocol);
    void processDie(Protocol protocol);
    void processResurrect(Protocol protocol);

public:
    explicit ThGameModelServer(ThUserServer& th_user_server, int map_id,
        int game_id);
    virtual void processProtocol(Protocol& protocol) override;
    virtual void run() override;
    virtual void stop() override;
    void addThSender(ThSender* th_sender);
    void echoProtocol(Protocol protocol);
    void removePlayer(int user_id);
    virtual bool isDone() override;
    bool wasLaunched();
    ~ThGameModelServer();
};

#endif
