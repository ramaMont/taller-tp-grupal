#include "ThDrawer.h"
#include <chrono>

ThDrawer::ThDrawer(Window &window, Screen &screen): 
        Thread(), window(window), screen(screen){
}
void ThDrawer::run(){
    while (is_running){
         window.set_no_color();
         screen.show();
         window.render(); 
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
}

void ThDrawer::stop(){
    is_running = false;
}

ThDrawer::~ThDrawer(){
}
