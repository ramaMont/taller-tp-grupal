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
        protagonist_id(protagonist_id),is_running(true) {
    player.set_texture(&texture);
    player.newGunType(1);
    initDirections();
    initMap(map_filename);
}

/* 
Inicializo el diccionario directions para acceder a cada direccion 
en tiempo O(1)
 */
void GameModelClient::initDirections(){
    DirAhead* forward = new DirAhead();
    DirBehind* backward = new DirBehind();
    DirLeft* left = new DirLeft();
    DirRight* right = new DirRight();
    DirRotLeft* rotLeft = new DirRotLeft();
    DirRotRight* rotRight = new DirRotRight();
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
//                   map.addPositionable(posicionable,position);                
//               }else if(pos_value==2){
//                   Posicionable *posicionable = new Wall_bluestone(position);
//                   posicionable->set_texture(&texture);
//                   map.addPositionable(posicionable,position);
//               }else if(pos_value==3){
//                   Posicionable *posicionable = new Wall_purplestone(position);
//                   posicionable->set_texture(&texture);
//                   map.addPositionable(posicionable,position);
//               }else if(pos_value==4){
//                   Posicionable *posicionable = new Wall_colorstone(position);
//                   posicionable->set_texture(&texture);
//                   map.addPositionable(posicionable,position);
//               }else if(pos_value==5){
//                   Posicionable *posicionable = new Wall_eagle(position);
//                   posicionable->set_texture(&texture);
//                   map.addPositionable(posicionable,position);
//               }else if(pos_value==6){
//                   Posicionable *posicionable = new Wall_mossy(position);
//                   posicionable->set_texture(&texture);
//                   map.addPositionable(posicionable,position);
//               }else if(pos_value==7){
//                   Posicionable *posicionable = new Wall_redbrick(position);
//                   posicionable->set_texture(&texture);
//                   map.addPositionable(posicionable,position);
//               }
//             }else if(pos_value<10){
//               Coordinates position((float)i+0.5,(float)j+0.5);
//               SpriteHolder *posicionable = new SpriteHolder(position,a_map[i][j]-8,player);
//               posicionable->set_texture(&texture);
//               posicionable->add_sprite(2);
//               sprites.push_back(posicionable);
//               map.addPositionable(posicionable,position);
//             }else{//DOOR==10
//               Coordinates position((float)i,(float)j);
//               Door *posicionable = new Door(position);
//               posicionable->set_texture(&texture);
//               door = posicionable;
//               map.addPositionable(posicionable,position);   
//             }
//             /*else{ DEJO DE AGREGAR ENEMIGOS ASI
//               Coordinates position((float)i+0.5,(float)j+0.5);
//               Coordinates enemy_direction(0,1);
//               Enemy *posicionable = new Enemy(texture,position,a_map[i][j]-10,enemy_direction,map,player,"Andy");//Esta textura ahora mismo representa si esta de costado o de frente, deberia representar qué enemigo es
//               posicionable->newEnemyType(1);//Tipo de enemmigo por defecto
//               sprites.push_back(posicionable);
//               enemies.push_back(posicionable);
//               map.addPositionable(posicionable,position);             
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
                  Posicionable *posicionable = new WallGreystone(position);
                  posicionable->set_texture(&texture);
                  map.addPositionable(posicionable,position);   
            }else if (elemento == "wall_bluestone"){
                  Posicionable *posicionable = new WallBluestone(position);
                  posicionable->set_texture(&texture);
                  map.addPositionable(posicionable,position);   
            }else if (elemento == "wall_colorstone"){
                  Posicionable *posicionable = new WallColorstone(position);
                  posicionable->set_texture(&texture);
                  map.addPositionable(posicionable,position);   
            }else if (elemento == "passage"){
                Posicionable *posicionable = new WallEagle(position);
                posicionable->set_texture(&texture);
                map.addPositionable(posicionable,position);  
            }else if (elemento == "door"){
                Door *posicionable = new Door(position);
                posicionable->set_texture(&texture);
                doors.push_back(posicionable);
                map.addPositionable(posicionable,position);   
            }else{
              position.x+=0.5;
              position.y+=0.5;
            }
            if (elemento == "barrel"){
               SpriteHolder *posicionable = new SpriteHolder(position,0,player);
               posicionable->set_texture(&texture);
               posicionable->isColidable();
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }else if (elemento == "pillar"){
               SpriteHolder *posicionable = new SpriteHolder(position,1,player);
               posicionable->set_texture(&texture);
               posicionable->isColidable();
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }else if (elemento == "greenlight"){
               SpriteHolder *posicionable = new SpriteHolder(position,2,player);
               posicionable->set_texture(&texture);
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position); 
            }else if (elemento == "trophie"){
               printf("El trofeo está en: (%f,%f)\n",position.x,position.y );
               SpriteHolder *posicionable = new SpriteHolder(position,3,player);
               posicionable->set_texture(&texture);
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }else if (elemento == "rocket_launcher"){
              std::cout<<"elemento:"<<elemento<<std::endl;
               SpriteHolder *posicionable = new SpriteHolder(position,4,player);
               posicionable->set_texture(&texture);
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }else if (elemento == "medicine"){
              std::cout<<"elemento:"<<elemento<<std::endl;
               SpriteHolder *posicionable = new SpriteHolder(position,5,player);
               posicionable->set_texture(&texture);
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }else if (elemento == "machine_gun"){
               SpriteHolder *posicionable = new SpriteHolder(position,6,player);
               posicionable->set_texture(&texture);
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }else if (elemento == "key"){
               SpriteHolder *posicionable = new SpriteHolder(position,7,player);
               posicionable->set_texture(&texture);
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }else if (elemento == "food"){
               SpriteHolder *posicionable = new SpriteHolder(position,8,player);
               posicionable->set_texture(&texture);
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }else if (elemento == "fire_canon"){
               SpriteHolder *posicionable = new SpriteHolder(position,9,player);
               posicionable->set_texture(&texture);
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }else if (elemento == "bullets"){
               SpriteHolder *posicionable = new SpriteHolder(position,10,player);
               posicionable->set_texture(&texture);
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }else if (elemento == "table"){
               SpriteHolder *posicionable = new SpriteHolder(position,11,player);
               posicionable->set_texture(&texture);
               posicionable->isColidable();
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }
        }
    }
    map.addPlayer(&player);
}

void GameModelClient::cleanDirections(){
    /*for (auto it = directions.begin(); it != directions.end(); ++it){
        Direccion* dir = it->second;
        delete(dir);
    }*/
}

void GameModelClient::processMove(Protocol& protocol){
    Character* character = characters.at(protocol.getId());
    Direction* dir = directions.at(protocol.getDirection());
    character->move(dir);
    if(protocol.getId()!=protagonist_id){
      Enemy* enemy = dynamic_cast<Enemy*>(character);
      enemy->moving();
    }
}

void GameModelClient::addPlayer(Protocol& protocol){ //Playeres O enemigos
    auto protocol_position = protocol.getPosition();
    Coordinates player_position((double)std::get<0>(protocol_position), (double)std::get<1>(protocol_position));
    Protocol::direction player_direction = protocol.getDirection();
    Coordinates initial_direction(player_direction);
    int player_id = protocol.getUserId();

    if(player_id == protagonist_id){
        try{
            added_player = true;
            Coordinates initial_position = player_position;
            player.complete(initial_position, initial_direction,player_id);
            characters.insert(std::pair<int, Player*>(player_id, &player));
            map.addPositionable(&player,initial_position);  
            player.setInitialPosition(initial_position);
        } catch(...){
        }
    }else{
        try{
            Coordinates initial_position = player_position;
            Enemy* enemy = new Enemy(initial_position, initial_direction, map, player,player_id);
            enemy->set_texture(&texture);
            enemy->newEnemyType(1);
            sprites.push_back(enemy);
            enemies.push_back(enemy);
            map.addPositionable(enemy,initial_position);    
            characters.insert(std::pair<int, Character*>(player_id, enemy));
        } catch(...){
        }        
    }
}


void GameModelClient::removePlayer(int id){
    Character* removableEnemy = characters[id];
    map.removePositionable(removableEnemy->get_position());
    characters.erase(id);
    //Y me falta eliminarlos tambien del vector sprites y del vector enemies

}

void GameModelClient::player_shoot(){
  player.shoot();
}

Player& GameModelClient::getPlayer(){
    return player;
}

Window& GameModelClient::getWindow(){
  return window;
}
    
Screen& GameModelClient::getScreen(){
  return screen;
}

Character& GameModelClient::getEnemy(int user_id){
    return *characters.at(user_id);
}

void  GameModelClient::updateFrameAnimations(){
    for(unsigned int i=0; i<enemies.size(); i++){
        enemies[i]->updateFrame();
    }
    player.updateShots();
    // TODO: agregar vector de puertas
    for(auto& door : doors){
        door->updateFrame();
    }
}

void GameModelClient::showWindow(){
    window.showWindow();
}

void GameModelClient::hideWindow(){
    window.hideWindow();
}

ClMap& GameModelClient::getMap(){
    return map;
}

int GameModelClient::getId(){
    return game_id;
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
            auto character = characters.at(protocol.getId());
            character->die();
            break;
        }
        case Protocol::action::RESURRECT:{
            auto character = characters.at(protocol.getId());
            character->resurrect();
            break;
        }
        case Protocol::action::REMOVE:
            removePlayer(protocol.getUserId());
            break;
        case Protocol::action::OPEN:
            openDoor(protocol);
            break;
        case Protocol::action::OPENING:
            openingDoor(protocol);
            break;
        case Protocol::action::CLOSE:
            closeDoor(protocol);
            break;
        case Protocol::action::ADDPOINTS:
            player.addPoints(protocol.getDamage());
            break;
        case Protocol::action::UPDATE_HEALTH:
            player.updateHealth(protocol.getDamage());
            break;
        case Protocol::action::UPDATE_BULLETS:
            player.updateAmmo(protocol.getDamage());
            break;
        case Protocol::action::PICKUP:
            processPickup(protocol);
            break;
        case Protocol::action::SWITCH_GUN:
            player.newGunType(protocol.getDamage());
            break;
        case Protocol::action::END_GAME_KILLS:
            
            _ordered_players_kills.push_back(
                std::pair<int, int>(protocol.getDamage(), 
                protocol.getId()));
            break;
        case Protocol::action::END_GAME_POINTS:
            _ordered_players_points.push_back(
                std::pair<int, int>(protocol.getDamage(), 
                protocol.getId()));
            break;
        case Protocol::action::END_GAME_BULLETS:
            _ordered_players_bullets.push_back(
                std::pair<int, int>(protocol.getDamage(), 
                protocol.getId()));
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
    }else{
      Character* character= characters[protocol.getId()];
      Enemy* enemy = dynamic_cast<Enemy*>(character);
      enemy->shoot();
    }
}

void GameModelClient::processShooted(Protocol protocol){
    player.updateHealth(protocol.getDamage());
}

void GameModelClient::processPickup(Protocol& protocol){
    Coordinates position(protocol.getPosition());
    /*printf("El sprite a eliminar está en: (%f,%f)\n",position.x,position.y );
    SpriteHolder* sprite = static_cast<SpriteHolder*>(map.getPositionableIn(position));
    sprite->has_character();
    if(sprite->has_character()){
      Character* character = sprite->get_character();
      map.removeSpriteWithCharacter(position,character);
    }else{
      map.removePositionable(position);
    }*/
    //delete sprite;
}


void GameModelClient::push(Protocol protocol){
    operations.push(protocol);
}

void GameModelClient::openDoor(const Protocol& protocol){
    Coordinates door_pos(protocol.getPosition());
    Door* door = static_cast<Door*>(map.getPositionableIn(door_pos));
    door->setState("open");
}

void GameModelClient::openingDoor(const Protocol& protocol){
    Coordinates door_pos(protocol.getPosition());
    Door* door = static_cast<Door*>(map.getPositionableIn(door_pos));
    door->setState("opening");
}

void GameModelClient::closeDoor(const Protocol& protocol){
    Coordinates door_pos(protocol.getPosition());
    Door* door = static_cast<Door*>(map.getPositionableIn(door_pos));
    door->setState("closed");
}

std::map<int,Character*> GameModelClient::getCharacters(){
    return characters;
}

GameModelClient::~GameModelClient(){
}
