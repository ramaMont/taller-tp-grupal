#include "GameModelClient.h"
#include <tuple>
#include <yaml-cpp/yaml.h>
#include <cmath>

#include "SpriteValues.h"

GameModelClient::GameModelClient(int user_id, std::string map_filename,\
            int game_id, int protagonist_id,int &_winner_id, bool& game_done,\
    std::vector<std::pair<int,int>> &_ordered_players_kills, std::vector<std::pair<int,int>> &_ordered_players_points,\
    std::vector<std::pair<int,int>> &_ordered_players_bullets) : 
        window(640,480,320,200) ,
        texture(window), map(), 
        added_player(false),player(map),
        operations(), game_id(game_id),
        screen(rockets,enemies,sprites,player,map,texture,window),
        protagonist_id(protagonist_id),is_running(true),
        _sound_player(), _has_ended(false), _winner_id(_winner_id),
        game_done(game_done),_ordered_players_kills(_ordered_players_kills),
        _ordered_players_points(_ordered_players_points),_ordered_players_bullets(_ordered_players_bullets)   {

    _winner_id = -1;
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
            }else if (elemento == "wall_pruplestone"){
                  Posicionable *posicionable = new WallPurplestone(position);
                  posicionable->set_texture(&texture);
                  map.addPositionable(posicionable,position);   
            }else if (elemento == "wall_redbrick"){
                  Posicionable *posicionable = new WallRedbrick(position);
                  posicionable->set_texture(&texture);
                  map.addPositionable(posicionable,position);   
            }else if (elemento == "wall_wood"){
                  Posicionable *posicionable = new WallWood(position);
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
               SpriteHolder *posicionable = new SpriteHolder(position,texture_values.at(elemento),player);
               posicionable->set_texture(&texture);
               posicionable->isColidable();
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }else if (elemento == "pillar"){
               SpriteHolder *posicionable = new SpriteHolder(position,texture_values.at(elemento),player);
               posicionable->set_texture(&texture);
               posicionable->isColidable();
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }else if (elemento == "greenlight"){
               SpriteHolder *posicionable = new SpriteHolder(position,texture_values.at(elemento),player);
               posicionable->set_texture(&texture);
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position); 
            }else if (elemento == "trophie"){
               SpriteHolder *posicionable = new SpriteHolder(position,texture_values.at(elemento),player);
               posicionable->set_texture(&texture);
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }else if (elemento == "rocket_launcher"){
               SpriteHolder *posicionable = new SpriteHolder(position,texture_values.at(elemento),player);
               posicionable->set_texture(&texture);
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }else if (elemento == "medicine"){
               SpriteHolder *posicionable = new SpriteHolder(position,texture_values.at(elemento),player);
               posicionable->set_texture(&texture);
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }else if (elemento == "machine_gun"){
               SpriteHolder *posicionable = new SpriteHolder(position,texture_values.at(elemento),player);
               posicionable->set_texture(&texture);
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }else if (elemento == "key"){
               SpriteHolder *posicionable = new SpriteHolder(position,texture_values.at(elemento),player);
               posicionable->set_texture(&texture);
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }else if (elemento == "food"){
               SpriteHolder *posicionable = new SpriteHolder(position,texture_values.at(elemento),player);
               posicionable->set_texture(&texture);
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }else if (elemento == "fire_canon"){
               SpriteHolder *posicionable = new SpriteHolder(position,texture_values.at(elemento),player);
               posicionable->set_texture(&texture);
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }else if (elemento == "bullets"){
               SpriteHolder *posicionable = new SpriteHolder(position,texture_values.at(elemento),player);
               posicionable->set_texture(&texture);
               sprites.push_back(posicionable);
               map.addPositionable(posicionable,position);
            }else if (elemento == "table"){
               SpriteHolder *posicionable = new SpriteHolder(position,texture_values.at(elemento),player);
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
    for (auto& dir : directions){
        delete(dir.second);
    }
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

// void GameModelClient::player_shoot(){
//     player.shoot();
// }

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

void GameModelClient::addDeadSprite(Coordinates position, CharacterType character_type){
  //printf("El personaje muerto es: %i \n", a_character_type);
  if(character_type==dog){
    SpriteHolder *posicionable = new SpriteHolder(position,texture_values.at("dead_dog"),player);
    posicionable->set_texture(&texture);
    sprites.push_back(posicionable);  
    map.addPositionable(posicionable,position);  
  }else if(character_type==guard){
    SpriteHolder *posicionable = new SpriteHolder(position,texture_values.at("dead_guard"),player);
    posicionable->set_texture(&texture);
    sprites.push_back(posicionable);  
    map.addPositionable(posicionable,position);  
  }/*else if(character_type==2){
    SpriteHolder *posicionable = new SpriteHolder(position,15,player);
    posicionable->set_texture(&texture);
    sprites.push_back(posicionable);  
    map.addPositionable(posicionable,position);  
  }else if(character_type==3){
    SpriteHolder *posicionable = new SpriteHolder(position,16,player);
    posicionable->set_texture(&texture);
    sprites.push_back(posicionable);  
    map.addPositionable(posicionable,position);  
  }else if(character_type==4){
    SpriteHolder *posicionable = new SpriteHolder(position,17,player);
    posicionable->set_texture(&texture);
    sprites.push_back(posicionable);  
    map.addPositionable(posicionable,position);  
  }*/
}


void GameModelClient::removeCharacterFromMap(int id){
    Character* removableCharacter = characters[id];
    Coordinates removablePosition = removableCharacter->get_position();
    unsigned int i=0;
    bool done = false;
    while(i<sprites.size() and !done){     //Me fijo si hay un sprite en esa posicion
    	SpriteHolder* sprite = sprites[i];
    	Coordinates sprite_position = sprite->get_position();
    	if(sprite_position == removablePosition){
    		done = true;
    		sprite->remove();
    	}
    	i++;
    }
    i=0;
    while(i<doors.size() and !done){     //Me fijo si hay una puerta en esa posicion
    	Coordinates door_position = doors[i]->getPosicion();
    	if(door_position == removablePosition){
    		done = true;
    		doors[i]->remove();
    	}
    	i++;
    }
    if(!done){
    	map.removePositionable(removablePosition);
    }
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
            //CharacterType character_type = character->getType();
            //Coordinates position = character->getPosicion();
            //character->die();
            //addDeadSprite(position,character_type);
            removeCharacterFromMap(protocol.getId());
            playSound(SoundPlayer::sound_type::DYING, character);
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
        case Protocol::action::THROW:
            processThrow(protocol);
            break;
        case Protocol::action::SWITCH_GUN:
            processGunSwitch(protocol);
            break;
        case Protocol::action::OPEN_PASSAGE:
            map.removePositionable(Coordinates(protocol.getPosition()));
            break;
        case Protocol::action::ROCKET:
            processRocket(protocol);
            break;
        case Protocol::action::MOVE_ROCKET:
            processRocket(protocol);
            break;
        case Protocol::action::EXPLOSION:
            processExplosion(protocol);
            break;
        case Protocol::action::KEY:
            processKey(protocol);
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
        case Protocol::action::WINNER:
            _winner_id = protocol.getId();
            break;
        case Protocol::action::ENDGAME:
            endGame();
            break;
        default:
            break;
    }
}

void GameModelClient::run(){
    while (!operations.empty() && !_has_ended){
        Protocol protocol = operations.front();
        operations.pop();
        processProtocol(protocol);
    }
}

void GameModelClient::processShoot(Protocol protocol){
    if (protagonist_id == protocol.getId()){
        player.shoot(_sound_player, 0);
        // _sound_player.playSound(SoundPlayer::sound_type::PISTOL_SHOOT, 100);
    }else{
        Character* character= characters[protocol.getId()];
        Enemy* enemy = dynamic_cast<Enemy*>(character);
        float distance = calculateDistanceBetween(enemy);
        enemy->shoot(_sound_player, distance);
        // playSound(SoundPlayer::sound_type::PISTOL_SHOOT, character);
    }
}

void GameModelClient::processShooted(Protocol protocol){
    player.updateHealth(protocol.getDamage());
}

void GameModelClient::processPickup(Protocol& protocol){
    Coordinates position(protocol.getPosition());
    SpriteHolder* sprite = static_cast<SpriteHolder*>
        (map.getPositionableIn(position));
    if(sprite->hasCharacter()){
      Movable* character = sprite->getCharacter();
      map.removeSpriteWithCharacter(position,character);
    }else{
      map.removePositionable(position);
    }
}

void GameModelClient::processThrow(Protocol& protocol){
    Coordinates position(protocol.getPosition());
    SpriteHolder *posicionable = new 
        SpriteHolder(position,protocol.getId(),player);
    posicionable->set_texture(&texture);
    sprites.push_back(posicionable);
    map.addPositionable(posicionable,position);
}

void GameModelClient::processGunSwitch(Protocol& protocol){
    if (protagonist_id == protocol.getId()){
        player.newGunType(protocol.getDamage());
    }else{
        Character* character= characters[protocol.getId()];
        Enemy* enemy = dynamic_cast<Enemy*>(character);
        enemy->newEnemyType(protocol.getDamage());
    }
}

void GameModelClient::processRocket(Protocol& protocol){ //Por ahora pruebo con un solo rocket
  Coordinates position(protocol.getFloatPosition());
  if (protocol.getAction() == Protocol::action::MOVE_ROCKET){
      //printf("x cambiarle la posicion, supuestamente está en: (%f,%f)\n",position.x,position.y);
      bool found = false;
      unsigned int i = 0;
      Rocket* rocket;
      while(i<rockets.size() and !found){
        rocket = rockets[i];
        //printf("Pero en realidad está en: (%f,%f)\n",rocket->getPosicion().x,rocket->getPosicion().y );
        if(position==rocket->getPosicion()){
          found = true;
          rocket->move();
          //printf("le cambie la posicion, ahora es: (%f,%f)\n\n",rocket->getPosicion().x,rocket->getPosicion().y);
        }
        i++;
      }
  }else{ //Creo el misil
      Rocket* rocket = new Rocket(position,player.getDirection() ,map, player);
      rocket->set_texture(&texture);
      rockets.push_back(rocket);
      map.addPositionable(rocket,position);  
      //printf("cree uno nuevo en: (%f,%f)\n\n", position.x,position.y);
  }
}

void GameModelClient::processExplosion(Protocol& protocol){
	Coordinates position(protocol.getFloatPosition());
    bool found = false;
    unsigned int i = 0;
    Rocket* rocket;
    printf("posicion recibida: (%f,%f)\n",position.x,position.y );
    while(i<rockets.size() and !found){
        rocket = rockets[i];
        printf("posicion de mi rockett: (%f,%f)\n",rocket->getPosicion().x,rocket->getPosicion().y );
        //printf("Pero en realidad está en: (%f,%f)\n",rocket->getPosicion().x,rocket->getPosicion().y );
        if(position==rocket->getPosicion()){
          printf("aa\n");
          found = true;
          playSound(SoundPlayer::sound_type::ROCKET_EXPLOTION, rocket);
          map.removePositionable(position);
          rockets.erase(rockets.begin() + i);
          //printf("le cambie la posicion, ahora es: (%f,%f)\n\n",rocket->getPosicion().x,rocket->getPosicion().y);
        }
        i++;
    }


    //auto rocket_pos = rockets[0]->get_position();
	//map.removePositionable(rockets[0]->get_position());
}

void GameModelClient::processKey(Protocol& protocol){
    if (protagonist_id != protocol.getId())
        return;
    player.updateKeys(protocol.getDamage());
}


void GameModelClient::push(Protocol protocol){
    operations.push(protocol);
}

void GameModelClient::openDoor(const Protocol& protocol){
    Coordinates door_pos(protocol.getPosition());
    Door* door = static_cast<Door*>(map.getPositionableIn(door_pos));
    door->setState(open);
}

void GameModelClient::openingDoor(const Protocol& protocol){
    Coordinates door_pos(protocol.getPosition());
    Door* door = static_cast<Door*>(map.getPositionableIn(door_pos));
    door->setState(opening);
    playSound(SoundPlayer::sound_type::DOOR_OPENING, 
        map.getPositionableIn(door_pos));
}

void GameModelClient::closeDoor(const Protocol& protocol){
    Coordinates door_pos(protocol.getPosition());
    Door* door = static_cast<Door*>(map.getPositionableIn(door_pos));
    door->setState(closed);
    playSound(SoundPlayer::sound_type::DOOR_CLOSING, 
        map.getPositionableIn(door_pos));
}

std::map<int,Character*> GameModelClient::getCharacters(){
    return characters;
}

float GameModelClient::calculateDistanceBetween(Posicionable* positionable){
    Coordinates player_position = this->player.get_position();
    Coordinates positionable_position = positionable->get_position();
    return std::sqrt(std::pow(player_position.x - positionable_position.x, 2)
        + std::pow(player_position.y - positionable_position.y, 2));
}

void GameModelClient::playSound(SoundPlayer::sound_type sound_type, Posicionable* positionable){
    float distance = calculateDistanceBetween(positionable);
    int volume = _sound_player.calculateVolume(distance);
    _sound_player.playSound(sound_type, volume);   
}


void GameModelClient::endGame(){
    // Mostrar pantalla con puntuaciones y ganador
    //int position = 1;
    if (!_has_ended){
        _has_ended = true;
        waitForAction(Protocol::action::ENDGAME);
        game_done = true;
        /*if (_winner_id != -1){
            std::cout << "The winner is Player ID: " << _winner_id << std::endl;
        } else {
            std::cout << "TIME IS OVER\n";
        }
        for (auto& player : _ordered_players_kills){
            std::cout << "Position " << position << " Player_ID: " << player.second << " Kills: " << player.first << std::endl;
            ++position;
        }
        position = 1;
        for (auto& player : _ordered_players_points){
            std::cout << "Position " << position << " Player_ID: " << player.second << " Points: " << player.first << std::endl;
            ++position;
        }
        position = 1;
        for (auto& player : _ordered_players_bullets){
            std::cout << "Position " << position << " Player_ID: " << player.second << " Bullets: " << player.first << std::endl;
            ++position;
        }*/
    }
}

void GameModelClient::waitForAction(Protocol::action desired_action){
    bool ready = false;
    while (!ready){
        if (operations.size() > 0){
            Protocol protocol = operations.front();
            operations.pop();
            if (protocol.getAction() == desired_action)
                ready = true;
            else
                processProtocol(protocol);
        }
    }
}

GameModelClient::~GameModelClient(){
    cleanDirections();
}
