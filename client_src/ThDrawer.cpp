#include "ThDrawer.h"

ThDrawer::ThDrawer(Player& player, Mapa& map): 
        window(640,480), ray_casting(player, map, window){
}
void ThDrawer::run(){
    window.set_no_color();
    ray_casting.calculate_ray_casting();
    window.render();
}

ThDrawer::~ThDrawer(){
}
