#ifndef __TH_GAME_MODEL_CLIENT__
#define __TH_GAME_MODEL_CLIENT__

#include <GameModel.h>
#include "ThUserClient.h"

class ThGameModelClient : public GameModel{
public:
    explicit ThGameModelClient(int user_id, int map_id, int game_id);
    explicit ThGameModelClient(Mapa&& map, std::map<int,Player>&& players);
    virtual void processProtocol(Protocol& protocol) override;
    virtual void run() override;
    virtual void stop() override;
    ~ThGameModelClient();
};

#endif
