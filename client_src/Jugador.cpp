#include "Jugador.h"

#include "texture.h"

Jugador::Jugador(Coordinates posicion,Coordinates direction ,Cl_Mapa& mapa, int id):
      Movable(posicion,direction,mapa,id), 
      shot_frame(0), gun_type(nullptr),
      shooting(false),score(10), lives(5), health(100), ammo(20){
//   	mapa.agregarJugador(this);
}

Jugador::Jugador(Cl_Mapa& mapa):
      Movable(Coordinates(4,4),Coordinates(1,0),mapa,0), 
      shot_frame(0), gun_type(nullptr),shooting(false),
      score(1000), lives(5), health(98), ammo(20){
//    mapa.agregarJugador(this);
}

void Jugador::complete(Coordinates initial_position,Coordinates initial_direction,int player_id){
   this->initial_position = initial_position;
   this->initial_direction = initial_direction;
   this->posicion = initial_position;
   this->direction = initial_direction;
   this->id = player_id;
}

void Jugador::resurrect(){
  //TODO: Resetear vida y demas atributos
    posicion = initial_position;
    direction = initial_direction;
    lives--;
    health = 100;
    mapa.agregarPosicionable(this, this->initial_position);
}

void Jugador::new_gun_type(int new_gun_type){
   	if(gun_type!=nullptr)
        delete gun_type;
   	if(new_gun_type==0)
        gun_type = new Knife(texture_drawer);
   	else if(new_gun_type==1)
        gun_type = new Gun(texture_drawer);
   	else if(new_gun_type==2)
        gun_type = new Machine_gun(texture_drawer);
   	else if(new_gun_type==3)
        gun_type = new Chain_gun(texture_drawer);
    fire_rate = gun_type->get_fire_rate();
}

void Jugador::shoot(){
  shooting = true;
  struct timeval time_now{};
  gettimeofday(&time_now, nullptr);
  time_shot_start = (time_now.tv_usec / 1000);    
}

bool Jugador::can_shoot(){
  return !shooting; //Solo puede disparar si no estaba disparando antes

}

void Jugador::update_shots(){
  if(shooting){
    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    time_t current_time = (time_now.tv_usec / 1000);      
    if(current_time<time_shot_start){
      current_time+=1000;
    }
    if(current_time<time_shot_start+ (fire_rate/5))
      shot_frame = 1;
    else if(current_time<time_shot_start+ (2*fire_rate/5))
      shot_frame = 2;
    else if(current_time<time_shot_start+ (3*fire_rate/5))
      shot_frame = 3;
    else if(current_time<time_shot_start+ (4*fire_rate/5))
      shot_frame = 4;
    else{
      shot_frame = 0;
      shooting = false;
    }
  }
}

void Jugador::draw(){
   texture_drawer->show_life_bar(score, lives, health, ammo);
	gun_type->call_drawer(shot_frame);
}

void Jugador::updateHealth(int amount){
	health += amount;
}

Jugador::~Jugador(){
	if(gun_type!=nullptr)
		delete gun_type;
}
