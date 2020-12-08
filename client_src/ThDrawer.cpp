#include "ThDrawer.h"
#include <chrono>

ThDrawer::ThDrawer(Player& player, Mapa& map): 
        Thread(), window(640,480), ray_casting(player, map, window){
}
void ThDrawer::run(){
    while (is_running){
        window.set_no_color();
        ray_casting.calculate_ray_casting();
        window.render();
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
}

void ThDrawer::stop(){
    is_running = false;
}

ThDrawer::~ThDrawer(){
}
