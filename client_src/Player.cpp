#include "Player.h"

#include "texture.h"

#include <ConfigVariable.h>

#include <math.h>

Player::Player(ClientMap& map):
        Character(Coordinates(4,4),Coordinates(1,0),map,0), 
        max_health(configs[CONFIG::vida_maxima]), 
        init_bullets(configs[CONFIG::balas_iniciales]), 
        shot_frame(0), gun_type(nullptr),shooting(false),
        frames_per_shot(0), current_shoot_frame(0), 
        score(0), lives(configs[CONFIG::cantidad_de_vidas]),
        health(max_health), ammo(configs[CONFIG::balas_iniciales]),
        has_key_1(false), has_key_2(false), alive(true){}

void Player::complete(Coordinates initial_position,\
				Coordinates initial_direction,int player_id){
    this->initial_position = initial_position;
    this->initial_direction = initial_direction;
    this->posicion = initial_position;
    this->direction = initial_direction;
    this->id = player_id;
}

void Player::removeLive(){
    lives--;
    if(!hasLivesLeft()){
        alive=false;
    }
}

bool Player::hasLivesLeft(){
    return lives>0;
}

void Player::moveDeadPosition(Direction* direccion){
    Coordinates nuevaPos = direccion->move(this,direction);
    if(map.isInside(nuevaPos)){
        this->posicion = nuevaPos;    
    }else{
        Coordinates movimiento_unidireccional;
        movimiento_unidireccional.x = nuevaPos.x;
        movimiento_unidireccional.y = this->posicion.y;
        if(map.isInside(movimiento_unidireccional)){
            this->posicion = movimiento_unidireccional;
        }
        movimiento_unidireccional.x = this->posicion.x;
        movimiento_unidireccional.y = nuevaPos.y;
        if(map.isInside(movimiento_unidireccional)){
            this->posicion = movimiento_unidireccional;
        }
    }
}

void Player::resurrect(const Coordinates& res_pos){
  //TODO: Resetear vida y demas atributos
    posicion = res_pos;
    direction = initial_direction;
    health = max_health;
    has_key_1 = false;
    has_key_2 = false;
    map.addMovable(this, this->posicion);
}

void Player::newGunType(int new_gun_type){
   	if(gun_type!=nullptr)
        delete gun_type;
   	if(new_gun_type==0)
        gun_type = new Knife(texture_drawer);
   	else if (new_gun_type==1)
        gun_type = new Gun(texture_drawer);
   	else if (new_gun_type==2)
        gun_type = new MachineGun(texture_drawer);
   	else if (new_gun_type==3)
        gun_type = new ChainGun(texture_drawer);
    else
    	gun_type = new RocketLauncher(texture_drawer);
    frames_per_shot = gun_type->getFramesPerShot();
    current_shoot_frame = 0;
}

void Player::shoot(SoundPlayer& soundPlayer, float distance){
    shooting = true;
    current_shoot_frame = 0;
    gun_type->playWeaponSound(soundPlayer, distance);  
}

int Player::getFramesPerShot(){
    return frames_per_shot;
}

bool Player::gunAllowsContinuousShooting(){
    return gun_type->allowsContinuousShooting();
}

CharacterType Player::getType(){
    return gun_type->getType();
}

void Player::updateShots(){
    if (shooting){
        current_shoot_frame++;
        if (current_shoot_frame>frames_per_shot){
            current_shoot_frame=0;
            shooting=false;
        }
    }
}

 //portion_health:Cual de las 8 caras muestro en la barra de vida
void Player::draw(){
    if(alive){
        float portion_health = ((float)health*8.0)/(float)max_health;
        texture_drawer->showLifeBar(id, score, lives,health,
        				 ceil(portion_health), ammo, has_key_1, has_key_2);
        gun_type->callDrawer(current_shoot_frame);
    }else{
        texture_drawer->showDeadBar(id, score);
    }
}

void Player::updateHealth(int amount){
    health = amount;
}

void Player::updateAmmo(int amount){
    ammo = amount;
}

void Player::addPoints(int amount){
    score += amount;
}

void Player::updateKeys(int amount){
    switch (amount){
    case 0:
        has_key_1 = false;
        has_key_2 = false;
        break;
    case 1:
        has_key_1 = true;
        has_key_2 = false;
        break;
    case 2:
        has_key_1 = true;
        has_key_2 = true;
    }
}

Player::~Player(){
    if (gun_type!=nullptr)
        delete gun_type;
}
