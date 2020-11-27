#include "coordinates.h"
#include "player.h"

#include <math.h>

void Player::move_side(float inc){//-1 or +1
    Coordinates movement_direction = dir.get_perpendicular_direction();
    if(dir.y>=0){
        pos.increment_on_direction(movement_direction,inc);
    }else{
        pos.increment_on_direction(movement_direction,-inc);
    }
}

void Player::move_front(float inc){//-step or +step
    Coordinates movement_direction = dir;
    movement_direction.normalice_direction();
    pos.increment_on_direction(movement_direction,inc);
}

void Player::rotate_player(float inc){ //mayor o menor
    float new_x = dir.x*cos(inc) - dir.y*sin(inc);
    float new_y = dir.x*sin(inc) + dir.y*cos(inc);
    dir.x = new_x;
    dir.y = new_y;
}

Player::Player(float x_pos, float y_pos, float x_dir, float y_dir):
        pos(x_pos,y_pos), dir(x_dir,y_dir){ } 


Coordinates Player::get_coordinates(){
    return pos;
}

Coordinates Player::get_direction(){
    return dir;
}    

void Player::move_forward(){
    move_front(step_size);
}

void Player::move_backward(){
    move_front(-step_size);
}

void Player::move_left(){
    move_side(-step_size);
}

void Player::move_right(){
    move_side(step_size);
}

void Player::rotate_left(){
    rotate_player(rotation_size);
}

void Player::rotate_right(){
    rotate_player(-rotation_size);
}

