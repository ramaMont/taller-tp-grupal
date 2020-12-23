#ifndef __TH_DRAWER__
#define __TH_DRAWER__

#include "window.h"
#include "ray_casting.h"
#include <Mapa.h>
#include <Player.h>
#include <Thread.h>

class ThDrawer : public Thread{
private:
    Window window;
    Raycasting ray_casting;
public:
    explicit ThDrawer(Player& player, Mapa& map);
    virtual void run() override;
    virtual void stop() override;
    ~ThDrawer();
};

#endif
