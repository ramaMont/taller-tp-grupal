#ifndef __TH_GAME_MODEL_SERVER__
#define __TH_GAME_MODEL_SERVER__

#include <GameModel.h>
class ThUserServer;
#include "ThUserServer.h"

class ThGameModelServer : public GameModel{
private:
    std::map<int,ThSender *> users_sender;

public:
    explicit ThGameModelServer(ThUserServer& th_user_server, int map_id, int game_id);
    explicit ThGameModelServer(Mapa&& map);
    virtual void processProtocol(Protocol& protocol) override;
    virtual void run() override;
    virtual void stop() override;
    void addThSender(ThSender* th_sender);
    void echoProtocol(Protocol protocol);
    void removePlayer(int user_id);
    virtual bool isDone() override;
    ~ThGameModelServer();
};

#endif
