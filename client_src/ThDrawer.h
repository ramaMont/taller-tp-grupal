#ifndef __TH_DRAWER__
#define __TH_DRAWER__

#include "window.h"
#include "ray_casting.h"
#include <Mapa.h>
#include <Player.h>

class ThDrawer{
private:
    Window window;
    Raycasting ray_casting;
public:
    explicit ThDrawer(Player& player, Mapa& map);
    void run();
    ~ThDrawer();
};

#endif
