#ifndef __TH_GAME_MODEL_SERVER__
#define __TH_GAME_MODEL_SERVER__

#include <GameModel.h>
class ThUserServer;
#include "ThUserServer.h"
#include "ThGameEvents.h"
#include "ThBots.h"

#include <atomic>
#include <map>

class ThGameModelServer : public GameModel{
private:
    std::map<int,ThSender *> users_sender;
    std::atomic<bool> launched;
    ThGameEvents th_game_events;
    ThBots th_bots;

    void processShoot(Protocol protocol);
    void processShooted(Protocol protocol);
    void processDie(Protocol protocol);
    void processResurrect(Protocol protocol);
    void processOpen(Protocol& protocol);

public:
    explicit ThGameModelServer(ThUserServer& th_user_server, std::string map_filename,
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
