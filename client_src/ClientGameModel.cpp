#include "ClientGameModel.h"

#include <thread>
#include <chrono>
#include <iostream>
#include <sys/time.h>

#include <vector>
#include <utility>

ClientGameModel::ClientGameModel(int map_id, int game_id, int protagonist_id):
    window(640,480,320,200) ,
    texture(window), map(24,24), 
    added_player(false),player(texture, map),
    operations(), game_id(game_id),
    screen(enemies,sprites,player,map,texture,window),
    protagonist_id(protagonist_id){
    initDirections();
    initMap();
    //Y aca le meto el for horrible para cargar todo el mapa?
} 

Window& ClientGameModel::get_window(){
  return window;
}

Screen& ClientGameModel::get_screen(){
  return screen;
}

void ClientGameModel::initMap(){
    std::vector<std::vector<int>> a_map{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    {1,0,8,10,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,9,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,9,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

    for(int i=0; i<24; i++){
      for(int j=0; j<24; j++){
        int pos_value = a_map[i][j];
        if(pos_value!=0){
            if(pos_value<8){
              Coordinates position((float)i,(float)j);
              if(pos_value==1){
                  Cl_Posicionable *posicionable = new Wall_greystone(texture,position);
                  map.agregarPosicionable(posicionable,position);                
              }else if(pos_value==2){
                  Cl_Posicionable *posicionable = new Wall_bluestone(texture,position);
                  map.agregarPosicionable(posicionable,position);
              }else if(pos_value==3){
                  Cl_Posicionable *posicionable = new Wall_purplestone(texture,position);
                  map.agregarPosicionable(posicionable,position);
              }else if(pos_value==4){
                  Cl_Posicionable *posicionable = new Wall_colorstone(texture,position);
                  map.agregarPosicionable(posicionable,position);
              }else if(pos_value==5){
                  Cl_Posicionable *posicionable = new Wall_eagle(texture,position);
                  map.agregarPosicionable(posicionable,position);
              }else if(pos_value==6){
                  Cl_Posicionable *posicionable = new Wall_mossy(texture,position);
                  map.agregarPosicionable(posicionable,position);
              }else if(pos_value==7){
                  Cl_Posicionable *posicionable = new Wall_redbrick(texture,position);
                  map.agregarPosicionable(posicionable,position);
              }
            }else if(pos_value<10){
              Coordinates position((float)i+0.5,(float)j+0.5);
              Sprite_holder *posicionable = new Sprite_holder(texture,position,a_map[i][j]-8,player);
              posicionable->add_sprite(2);
              sprites.push_back(posicionable);
              map.agregarPosicionable(posicionable,position);
            }/*else{ DEJO DE AGREGAR ENEMIGOS ASI
              Coordinates position((float)i+0.5,(float)j+0.5);
              Coordinates enemy_direction(0,1);
              Enemy *posicionable = new Enemy(texture,position,a_map[i][j]-10,enemy_direction,map,player,"Andy");//Esta textura ahora mismo representa si esta de costado o de frente, deberia representar qué enemigo es
              posicionable->new_enemy_type(1);//Tipo de enemmigo por defecto
              sprites.push_back(posicionable);
              enemies.push_back(posicionable);
              map.agregarPosicionable(posicionable,position);             
            }*/
        }
      }
    }
}
/* 
Inicializo el diccionario directions para acceder a cada direccion 
en tiempo O(1)
 */
void ClientGameModel::initDirections(){
    DirAdelante* forward = new DirAdelante();
    DirAtras* backward = new DirAtras();
    DirIzquierda* left = new DirIzquierda();
    DirDerecha* right = new DirDerecha();
    DirRotIzquierda* rotLeft = new DirRotIzquierda();
    DirRotDerecha* rotRight = new DirRotDerecha();
    directions[Protocol::direction::FORWARD] = forward;
    directions[Protocol::direction::BACKWARD] = backward;
    directions[Protocol::direction::LEFT] = left;
    directions[Protocol::direction::RIGHT] = right;
    directions[Protocol::direction::ROTATE_LEFT] = rotLeft;
    directions[Protocol::direction::ROTATE_RIGHT] = rotRight;
}

void ClientGameModel::cleanDirections(){
    /*for (auto it = directions.begin(); it != directions.end(); ++it){
        Direccion* dir = it->second;
        delete(dir);
    }*/
}

void ClientGameModel::processMove(Protocol& protocol){
    Movable* movable = movables.at(protocol.getId());
    Direccion* dir = directions.at(protocol.getDirection());
    movable->mover(dir);
}

/*void ClientGameModel::push(Protocol protocol){
    operations.push(protocol);
}*/

void ClientGameModel::addPlayer(int player_id){ //Jugadores O enemigos
    static int pos_x = 2;
    static int pos_y = 2;

    if(player_id == protagonist_id){
        try{
            added_player = true;
            Coordinates initial_position(pos_x, pos_y);
            Coordinates initial_direction(0, 1);
            player.complete(initial_position,initial_direction,player_id);
            movables.insert(std::pair<int, Jugador*>(player_id, &player));
            id_insertion_order.push_back(player_id);
            ++pos_x;
            ++pos_y;
        } catch(...){
        }
    }else{
        try{
            Coordinates initial_position(pos_x, pos_y);
            Coordinates initial_direction(0, 1);
            Enemy* enemy = new Enemy(texture,initial_position, initial_direction, map, player,player_id);
            sprites.push_back(enemy);
            enemies.push_back(enemy);
            map.agregarPosicionable(enemy,initial_position);    
            movables.insert(std::pair<int, Movable*>(player_id, enemy));
            id_insertion_order.push_back(player_id);
            ++pos_x;
            ++pos_y;
        } catch(...){
        }        
    }
}

void ClientGameModel::removePlayer(int id){
    Movable* removableEnemy = movables[id];
    map.delete_element(removableEnemy->get_position());
    movables.erase(id);
    //Y me falta eliminarlos tambien del vector sprites y del vector enemies

}


Jugador& ClientGameModel::getPlayer(){
    return player;
}

Movable& ClientGameModel::getEnemy(int user_id){
    return *movables.at(user_id);
}

Cl_Mapa& ClientGameModel::getMap(){
    return map;
}

int ClientGameModel::getId(){
    return game_id;
}

std::vector<int>& ClientGameModel::getIdsVector(){
    return id_insertion_order;
}

ClientGameModel& ClientGameModel::operator=(ClientGameModel&& other){
    if (this == &other){
        return *this;        // other is myself!
    }
    this->map = std::move(other.map);
    //this->is_running = true;
    //this->players = std::move(other.players);
    this->directions = std::move(other.directions);
    this->game_id = std::move(other.game_id);
    return *this;
}

void ClientGameModel::draw(SDL_bool &done){
    DirAdelante forward;
    DirAtras backward;
    DirIzquierda left;
    DirDerecha right;
    DirRotDerecha rotRight;
    DirRotIzquierda rotLeft;

    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    SDL_Event event;


        if(keys[SDL_SCANCODE_RIGHT])
          player.mover(&rotRight);
        if(keys[SDL_SCANCODE_LEFT])
          player.mover(&rotLeft);
        if(keys[SDL_SCANCODE_UP])
          player.mover(&forward);
        if(keys[SDL_SCANCODE_DOWN])
          player.mover(&backward);


        if(keys[SDL_SCANCODE_Z]){
          player.new_gun_type(0);
        }else if(keys[SDL_SCANCODE_X]){
          player.new_gun_type(1);
        }else if(keys[SDL_SCANCODE_C]){
          player.new_gun_type(2);
        }else if(keys[SDL_SCANCODE_V]){
          player.new_gun_type(3);
        }

        else if(keys[SDL_SCANCODE_RCTRL] or keys[SDL_SCANCODE_LCTRL]){
          player.shoot();
        }        

        player.update_shots();

        bool movement = false;

        if(keys[SDL_SCANCODE_W]){
          movement = true;
          enemies[0]->mover(&forward);
        }
        if(keys[SDL_SCANCODE_S]){
          movement = true;
          enemies[0]->mover(&backward);
        }
        if(keys[SDL_SCANCODE_A]){
          movement = true;
          enemies[0]->mover(&rotLeft);
        }
        if(keys[SDL_SCANCODE_D]){
          movement = true;
          enemies[0]->mover(&rotRight);
        }

        if(movement)
          enemies[0]->moving();
        else{
          enemies[0]->still();
        }

        if(keys[SDL_SCANCODE_1])
          enemies[0]->new_enemy_type(1);
        else if(keys[SDL_SCANCODE_2])
          enemies[0]->new_enemy_type(2);
        else if(keys[SDL_SCANCODE_3])
          enemies[0]->new_enemy_type(3);
        else if(keys[SDL_SCANCODE_4])
          enemies[0]->new_enemy_type(4);
        else if(keys[SDL_SCANCODE_0])
          enemies[0]->new_enemy_type(0);

        while (SDL_PollEvent(&event)) { 

          switch(event.type) {
            case SDL_QUIT: {
              done = SDL_TRUE;
            }
          }
        }

         window.set_no_color();
         screen.show();
         window.render(); 
      //SDL_Delay(5);
}

void ClientGameModel::run(){
  SDL_bool done = SDL_FALSE;

  time_t rate = 1000/30;

    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    time_t time_start = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
    time_t total_time = 0;
    time_t counter = 0;
    time_t max_time = 0;
    while(!done){
      //LLamo al dibujadorrr
      gettimeofday(&time_now, nullptr);
      time_t time = (time_now.tv_usec / 1000);
      //std::cout<<time<<std::endl;      
      draw(done);
      gettimeofday(&time_now, nullptr);
      time_t new_time = (time_now.tv_usec / 1000);
      //std::cout<<new_time<<std::endl<<std::endl<<std::endl;      

      if(new_time-time > max_time)
        max_time = new_time-time;
      if(new_time-time>0){
        total_time+=new_time-time;
        counter++;
      }

      gettimeofday(&time_now, nullptr);
      time_t time_after_draw = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);      
      time_t rest = rate - (time_after_draw - time_start);
      if (rest < 0){ //Me tardé mas que mi rate en dibujar este frame
            time_t behind = -rest; //Que tan atrasado estoy
            rest = rate - behind % rate; //
            time_t lost = behind + rest;
            time_start += lost;
      }else{
        std::this_thread::sleep_for(std::chrono::milliseconds(rest));
      }
      time_start += rate;
    }
    std::cout<<"El maximo fue: "<<max_time<<std::endl;
    std::cout<<"El tiempo promedio fue:"<<total_time/counter<<std::endl;
}

ClientGameModel::~ClientGameModel(){
    cleanDirections();
}
