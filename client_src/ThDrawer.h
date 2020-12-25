#ifndef __TH_DRAWER__
#define __TH_DRAWER__

#include "window.h"
#include "Screen.h"
#include <Cl_Mapa.h>
#include <Player.h>
#include <Jugador.h>
#include <Thread.h>

class ThDrawer : public Thread{
private:
    Window &window;
    Screen &screen;
public:
    explicit ThDrawer(Window &window, Screen &screen);
    virtual void run() override;
    virtual void stop() override;
    ~ThDrawer();
};

#endif
