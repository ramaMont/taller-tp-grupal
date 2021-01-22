#include "GameModelClient.h"
#include <tuple>
#include <yaml-cpp/yaml.h>

GameModelClient::GameModelClient(int user_id, std::string map_filename,
            int game_id, int protagonist_id) : 
        window(640,480,320,200) ,
        texture(window), map(), 
        added_player(false),player(map),
        operations(), game_id(game_id),
        screen(enemies,sprites,player,map,texture,window),
        protagonist_id(protagonist_id),door(nullptr),is_running(true) {
    player.set_texture(&texture);
    player.new_gun_type(1);
    initDirections();
    initMap(map_filename);
    addPlayer(user_id);
}

/* 
Inicializo el diccionario directions para acceder a cada direccion 
en tiempo O(1)
 */
void GameModelClient::initDirections(){
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

// void GameModelClient::initMap(){
//     std::vector<std::vector<int>> a_map{
//     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,2,2,10,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//     {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//     {1,0,8,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,9,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,9,0,0,0,0,1},
//     {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

//     for(int i=0; i<24; i++){
//       for(int j=0; j<24; j++){
//         int pos_value = a_map[i][j];
//         if(pos_value!=0){
//             if(pos_value<8){
//               Coordinates position((float)i,(float)j);
//               if(pos_value==1){
//                   Posicionable *posicionable = new Wall_greystone(position);
//                   posicionable->set_texture(&texture);
//                   map.agregarPosicionable(posicionable,position);                
//               }else if(pos_value==2){
//                   Posicionable *posicionable = new Wall_bluestone(position);
//                   posicionable->set_texture(&texture);
//                   map.agregarPosicionable(posicionable,position);
//               }else if(pos_value==3){
//                   Posicionable *posicionable = new Wall_purplestone(position);
//                   posicionable->set_texture(&texture);
//                   map.agregarPosicionable(posicionable,position);
//               }else if(pos_value==4){
//                   Posicionable *posicionable = new Wall_colorstone(position);
//                   posicionable->set_texture(&texture);
//                   map.agregarPosicionable(posicionable,position);
//               }else if(pos_value==5){
//                   Posicionable *posicionable = new Wall_eagle(position);
//                   posicionable->set_texture(&texture);
//                   map.agregarPosicionable(posicionable,position);
//               }else if(pos_value==6){
//                   Posicionable *posicionable = new Wall_mossy(position);
//                   posicionable->set_texture(&texture);
//                   map.agregarPosicionable(posicionable,position);
//               }else if(pos_value==7){
//                   Posicionable *posicionable = new Wall_redbrick(position);
//                   posicionable->set_texture(&texture);
//                   map.agregarPosicionable(posicionable,position);
//               }
//             }else if(pos_value<10){
//               Coordinates position((float)i+0.5,(float)j+0.5);
//               Sprite_holder *posicionable = new Sprite_holder(position,a_map[i][j]-8,player);
//               posicionable->set_texture(&texture);
//               posicionable->add_sprite(2);
//               sprites.push_back(posicionable);
//               map.agregarPosicionable(posicionable,position);
//             }else{//DOOR==10
//               Coordinates position((float)i,(float)j);
//               Door *posicionable = new Door(position);
//               posicionable->set_texture(&texture);
//               door = posicionable;
//               map.agregarPosicionable(posicionable,position);   
//             }
//             /*else{ DEJO DE AGREGAR ENEMIGOS ASI
//               Coordinates position((float)i+0.5,(float)j+0.5);
//               Coordinates enemy_direction(0,1);
//               Enemy *posicionable = new Enemy(texture,position,a_map[i][j]-10,enemy_direction,map,player,"Andy");//Esta textura ahora mismo representa si esta de costado o de frente, deberia representar qué enemigo es
//               posicionable->new_enemy_type(1);//Tipo de enemmigo por defecto
//               sprites.push_back(posicionable);
//               enemies.push_back(posicionable);
//               map.agregarPosicionable(posicionable,position);             
//             }*/
//         }
//       }
//     }
// }

void GameModelClient::initMap(std::string map_filename){
	std::string MAPS_PATH = "../data/maps/";
    YAML::Node map_node = YAML::LoadFile(MAPS_PATH + map_filename);
    int alto = map_node["filas"].as<int>();
    int ancho = map_node["columnas"].as<int>();
    map.resize(ancho, alto);
    YAML::Node map_elements = map_node["elementos"];
    std::string position="pos_";
    for (int i=0; i<alto; i++){
        for (int j=0; j<ancho; j++){
            std::string actual_position = position + std::to_string(i) + "_" +
                std::to_string(j);
            std::string elemento = map_elements[actual_position].as<std::string>();
            Coordinates position((float)i,(float)j);
            if (elemento == "wall_greystone"){
                  Posicionable *posicionable = new Wall_greystone(position);
                  posicionable->set_texture(&texture);
                  map.agregarPosicionable(posicionable,position);   
            }else if (elemento == "wall_bluestone"){
                  Posicionable *posicionable = new Wall_bluestone(position);
                  posicionable->set_texture(&texture);
                  map.agregarPosicionable(posicionable,position);   
            }else if (elemento == "wall_colorstone"){
                  Posicionable *posicionable = new Wall_colorstone(position);
                  posicionable->set_texture(&texture);
                  map.agregarPosicionable(posicionable,position);   
            }//Paredes, a partir de ahora meto sprites y los posiciono justo en medio del casillero
            position.x+=0.5;
            position.y+=0.5;
            if (elemento == "bullets"){
               Sprite_holder *posicionable = new Sprite_holder(position,2,player);
               posicionable->set_texture(&texture);
               posicionable->add_sprite(2);
               sprites.push_back(posicionable);
               map.agregarPosicionable(posicionable,position);
            }else if (elemento == "fire_canon"){
               Sprite_holder *posicionable = new Sprite_holder(position,2,player);
               posicionable->set_texture(&texture);
               posicionable->add_sprite(2);
               sprites.push_back(posicionable);
               map.agregarPosicionable(posicionable,position);
            }else if (elemento == "food"){
               Sprite_holder *posicionable = new Sprite_holder(position,2,player);
               posicionable->set_texture(&texture);
               posicionable->add_sprite(2);
               sprites.push_back(posicionable);
               map.agregarPosicionable(posicionable,position);
            }else if (elemento == "greenlight"){
               Sprite_holder *posicionable = new Sprite_holder(position,2,player);
               posicionable->set_texture(&texture);
               posicionable->add_sprite(2);
               sprites.push_back(posicionable);
               map.agregarPosicionable(posicionable,position); 
            }else if (elemento == "key"){
               Sprite_holder *posicionable = new Sprite_holder(position,2,player);
               posicionable->set_texture(&texture);
               posicionable->add_sprite(2);
               sprites.push_back(posicionable);
               map.agregarPosicionable(posicionable,position);
            }else if (elemento == "machine_gun"){
               Sprite_holder *posicionable = new Sprite_holder(position,2,player);
               posicionable->set_texture(&texture);
               posicionable->add_sprite(2);
               sprites.push_back(posicionable);
               map.agregarPosicionable(posicionable,position);
            }else if (elemento == "medicine"){
               Sprite_holder *posicionable = new Sprite_holder(position,2,player);
               posicionable->set_texture(&texture);
               posicionable->add_sprite(2);
               sprites.push_back(posicionable);
               map.agregarPosicionable(posicionable,position);
			}else if (elemento == "passage"){
                Posicionable *posicionable = new Wall_eagle(position);
                posicionable->set_texture(&texture);
                map.agregarPosicionable(posicionable,position);  
            }else if (elemento == "pillar"){
               Sprite_holder *posicionable = new Sprite_holder(position,1,player);
               posicionable->set_texture(&texture);
               sprites.push_back(posicionable);
               map.agregarPosicionable(posicionable,position);
            }else if (elemento == "rocket_launcher"){
               Sprite_holder *posicionable = new Sprite_holder(position,2,player);
               posicionable->set_texture(&texture);
               posicionable->add_sprite(2);
               sprites.push_back(posicionable);
               map.agregarPosicionable(posicionable,position);
            }else if (elemento == "trophie"){
               Sprite_holder *posicionable = new Sprite_holder(position,2,player);
               posicionable->set_texture(&texture);
               posicionable->add_sprite(2);
               sprites.push_back(posicionable);
               map.agregarPosicionable(posicionable,position);
            }else if (elemento == "machine_gun"){
               Sprite_holder *posicionable = new Sprite_holder(position,2,player);
               posicionable->set_texture(&texture);
               posicionable->add_sprite(2);
               sprites.push_back(posicionable);
               map.agregarPosicionable(posicionable,position);
            }else if (elemento == "barrel"){
               Sprite_holder *posicionable = new Sprite_holder(position,0,player);
               posicionable->set_texture(&texture);
               sprites.push_back(posicionable);
               map.agregarPosicionable(posicionable,position);
            }else if (elemento == "door"){
                Door *posicionable = new Door(position);
                posicionable->set_texture(&texture);
                door = posicionable;
                map.agregarPosicionable(posicionable,position);   
            }/*else if (elemento == "key_door"){
                Door *posicionable = new Door(position);
                posicionable->set_texture(&texture);
                door = posicionable;
                map.agregarPosicionable(posicionable,position);   
            }*/
        }
    }
    map.agregarJugador(&player);
}

void GameModelClient::cleanDirections(){
    /*for (auto it = directions.begin(); it != directions.end(); ++it){
        Direccion* dir = it->second;
        delete(dir);
    }*/
}

void GameModelClient::processMove(Protocol& protocol){
    Movable* movable = movables.at(protocol.getId());
    Direccion* dir = directions.at(protocol.getDirection());
    movable->mover(dir);
    if(protocol.getId()!=protagonist_id){
      Enemy* enemy = dynamic_cast<Enemy*>(movable);
      enemy->moving();
    }
}

void GameModelClient::addPlayer(int player_id){ //Jugadores O enemigos
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
            player.setInitialPosition(initial_position);
            ++pos_x;
            ++pos_y;
        } catch(...){
        }
    }else{
        try{
            Coordinates initial_position(pos_x, pos_y);
            Coordinates initial_direction(0, 1);
            Enemy* enemy = new Enemy(initial_position, initial_direction, map, player,player_id);
            enemy->set_texture(&texture);
            enemy->new_enemy_type(1);
            sprites.push_back(enemy);
            enemies.push_back(enemy);
            map.agregarPosicionable(enemy,initial_position);    
            movables.insert(std::pair<int, Movable*>(player_id, enemy));
            id_insertion_order.push_back(player_id);
            enemy->setInitialPosition(initial_position);
            ++pos_x;
            ++pos_y;
        } catch(...){
        }        
    }
}


void GameModelClient::removePlayer(int id){
    Movable* removableEnemy = movables[id];
    map.sacarPosicionable(removableEnemy->get_position());
    movables.erase(id);
    //Y me falta eliminarlos tambien del vector sprites y del vector enemies

}

void GameModelClient::player_shoot(){
  player.shoot();
}

Jugador& GameModelClient::getPlayer(){
    return player;
}

Door* GameModelClient::getDoor(){
  return door;
}

Window& GameModelClient::getWindow(){
  return window;
}
    
Screen& GameModelClient::getScreen(){
  return screen;
}

Movable& GameModelClient::getEnemy(int user_id){
    return *movables.at(user_id);
}

void  GameModelClient::updateFrameAnimations(){
  for(unsigned int i=0; i<enemies.size(); i++){
    enemies[i]->update_frame();
  }
  player.update_shots();
  if(door!=nullptr)
  	door->update_frame();
  //Y despues acá meter las puertas tambien
}

void GameModelClient::showWindow(){
    window.showWindow();
}

void GameModelClient::hideWindow(){
    window.hideWindow();
}

Cl_Mapa& GameModelClient::getMap(){
    return map;
}

int GameModelClient::getId(){
    return game_id;
}

std::vector<int>& GameModelClient::getIdsVector(){
    return id_insertion_order;
}

GameModelClient& GameModelClient::operator=(GameModelClient&& other){
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

void GameModelClient::processProtocol(Protocol& protocol){
    switch (protocol.getAction()){
        case Protocol::action::MOVE:
            processMove(protocol);
            break;
        case Protocol::action::SHOOT:
            processShoot(protocol);
            break;
        case Protocol::action::SHOOTED:
            processShooted(protocol);
            break;
        case Protocol::action::DIE:{
            auto movable = movables.at(protocol.getId());
            movable->die();
            break;
        }
        case Protocol::action::RESURRECT:{
            auto movable = movables.at(protocol.getId());
            movable->resurrect();
            break;
        }
        case Protocol::action::REMOVE:
            removePlayer(protocol.getUserId());
            break;
        case Protocol::action::OPEN:
            openDoor(protocol);
            break;
        default:
            break;
    }
}

void GameModelClient::run(){
    while (!operations.empty()){
        Protocol protocol = operations.front();
        operations.pop();
        processProtocol(protocol);
    }
}

void GameModelClient::processShoot(Protocol protocol){
    if (protagonist_id == protocol.getId()){
        player.shoot();
    }
}

void GameModelClient::processShooted(Protocol protocol){
    player.updateHealth(-protocol.getDamage());
}


void GameModelClient::push(Protocol protocol){
    operations.push(protocol);
}

void GameModelClient::openDoor(const Protocol& protocol){
    // TODO: con la posicion decirle a la puerta que se abra:
    // std::tuple<int, int> position = protocol.getPosition();
    // std::get<0>(position) += 1; // Accedo a la posicion X
    // std::get<1>(position) += 1; // Accedo a la posicion Y
    // pero por ahora:
    door->opening();
}

GameModelClient::~GameModelClient(){
}
