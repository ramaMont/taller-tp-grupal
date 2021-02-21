#include "GameModelClient.h"

#include <tuple>
#include <yaml-cpp/yaml.h>
#include <cmath>
#include <utility>
#include <map>
#include <string>
#include <vector>

#include "SpriteValues.h"

GameModelClient::GameModelClient(int user_id, const  std::string& map_filename,\
            int game_id, int protagonist_id,int &_winner_id, bool& game_done,\
            std::vector<std::pair<int,int>> &_ordered_players_kills,\
            std::vector<std::pair<int,int>> &_ordered_players_points,\
            std::vector<std::pair<int,int>> &_ordered_players_bullets,\
            int resolution_width, int resolution_height, bool fullscreen,\
            bool& player_alive, bool& have_winner) : 
    	GameModel(game_id),\
         window(resolution_width, resolution_height, fullscreen),\
         texture(window), map(),\
        added_player(false),player(map),\
        screen(rockets,enemies,sprites,player,map,texture,window),\
        protagonist_id(protagonist_id),is_running(true),\
        _sound_player(), _has_ended(false), _winner_id(_winner_id),\
        game_done(game_done),_ordered_players_kills(_ordered_players_kills),\
        _ordered_players_points(_ordered_players_points),\
        _ordered_players_bullets(_ordered_players_bullets),
        player_alive(player_alive), _have_winner(have_winner){
    _winner_id = -1;
    player.set_texture(&texture);
    player.newGunType(1);
    initMap(map_filename);
}
void GameModelClient::addPositionableToMap(Posicionable& posicionable){
  posicionable.set_texture(&texture);
  map.addPositionable(&posicionable,posicionable.get_position());
}

void GameModelClient::addWallsToMap(){
    int cant_walls = wallsGreystone.size();
    for (int i=0; i<cant_walls; i++){
      addPositionableToMap(wallsGreystone[i]);
    }
  
    cant_walls = wallsBluestone.size();
    for (int i=0; i<cant_walls; i++){
      addPositionableToMap(wallsBluestone[i]);
    }

    cant_walls = wallsColorstone.size();
    for (int i=0; i<cant_walls; i++){
      addPositionableToMap(wallsColorstone[i]);
    }

    cant_walls = wallsPurplestone.size();
    for (int i=0; i<cant_walls; i++){
      addPositionableToMap(wallsPurplestone[i]);
    }

    cant_walls = wallsRedbrick.size();
    for (int i=0; i<cant_walls; i++){
      addPositionableToMap(wallsRedbrick[i]);
    }

    cant_walls = wallsWood.size();
    for (int i=0; i<cant_walls; i++){
      addPositionableToMap(wallsWood[i]);
    }
}

void GameModelClient::createWall(const  std::string& elemento,\
        Coordinates position){
    if (elemento == "_greystone"){ 
        wallsGreystone.push_back(WallGreystone(position));
    } else if (elemento == "_bluestone"){
        wallsBluestone.push_back(WallBluestone(position)); 
    } else if (elemento == "_colorstone"){
        wallsColorstone.push_back(WallColorstone(position)); 
    } else if (elemento == "_pruplestone"){
        wallsPurplestone.push_back(WallPurplestone(position));    
    } else if (elemento == "_redbrick"){
        wallsRedbrick.push_back(WallRedbrick(position));    
    } else {
        wallsWood.push_back(WallWood(position));
    }
}

static bool is_sprite(const  std::string& elemento){
    return ((elemento == "barrel") or(elemento == "pillar") or\
        (elemento == "greenlight") or(elemento == "trophie") or\
        (elemento == "rocket_launcher") or(elemento == "medicine") or\
        (elemento == "machine_gun") or(elemento == "key") or\
        (elemento == "food") or(elemento == "fire_canon") or\
        (elemento == "bullets") or(elemento == "table"));
}

void GameModelClient::initMap(const  std::string& map_filename){
	const std::string MAPS_PATH = "../data/maps/";
    YAML::Node map_node = YAML::LoadFile(MAPS_PATH + map_filename);
    int alto = map_node["filas"].as<int>();
    int ancho = map_node["columnas"].as<int>();
    map.resize(ancho, alto);
    YAML::Node map_elements = map_node["elementos"];
    std::string pos="pos_";
    for (int i=0; i<alto; i++){
        for (int j=0; j<ancho; j++){
            std::string actual_position = pos + std::to_string(i) + "_" +
                std::to_string(j);
            std::string elemento = map_elements[actual_position].\
                as<std::string>();
            Coordinates position((float)i,(float)j);
            if ("wall" == elemento.substr(0,4)){
                createWall(elemento.substr(4), position);
            } else if ("passage" == elemento.substr(0,7)){
                createWall(elemento.substr(4), position);
            } else if (elemento == "door"){
                doors.push_back(Door(position,false));  
            } else if (elemento == "key_door"){//Cambiarle la textura
                doors.push_back(Door(position,true));  
            } else if (is_sprite(elemento)){
                position.x+=0.5;
                position.y+=0.5;
                SpriteHolder *posicionable = new 
                    SpriteHolder(position,player);
                posicionable->addSprite(texture_values.at(elemento));
                posicionable->set_texture(&texture);
                if ((elemento == "barrel") or (elemento == "pillar") or\
                        (elemento == "table")){
                    posicionable->isColidable();
                }
                sprites.push_back(posicionable);
                map.addPositionable(posicionable,position);
            }
        }
    }
    addWallsToMap();
    int cant_elements = doors.size();
    for (int i=0; i<cant_elements; i++){
        addPositionableToMap(doors[i]);
    }
    map.addPlayer(&player);
}

void GameModelClient::processMove(Protocol& protocol){
    Character* character = characters.at(protocol.getId());
    Direction* dir = directions.at(protocol.getDirection());
    character->move(dir);
    if (protocol.getId()!=protagonist_id){
      Enemy* enemy = static_cast<Enemy*>(character);
      enemy->moving();
    }
}

void GameModelClient::addPlayer(Protocol& protocol){ //Playeres O enemigos
    auto protocol_position = protocol.getPosition();
    Coordinates player_position((double)std::get<0>(protocol_position),\
        (double)std::get<1>(protocol_position));
    Protocol::direction player_direction = protocol.getDirection();
    Coordinates initial_direction(player_direction);
    int player_id = protocol.getUserId();

    if (player_id == protagonist_id){
        try{
            added_player = true;
            Coordinates initial_position = player_position;
            player.complete(initial_position, initial_direction,player_id);
            characters.insert(std::pair<int, Player*>(player_id, &player));
            map.addMovable(&player,initial_position);  
            player.setInitialPosition(initial_position);
        } catch(...){
        }
    } else{
        try{
            Coordinates initial_position = player_position;
            Enemy* enemy = new Enemy(initial_position, initial_direction, map,
                player,player_id);
            enemy->set_texture(&texture);
            enemy->newEnemyType(1);
            enemies.push_back(enemy);
            map.addMovable(enemy,initial_position);    
            characters.insert(std::pair<int, Character*>(player_id, enemy));
        } catch(...){
        }        
    }
}

void GameModelClient::removeEnemy(int id){
    Character* removableEnemy = characters[id];
    map.removePositionable(removableEnemy->get_position());
    characters.erase(id);
    int cant_enemies = enemies.size();
    for (int i=0; i<cant_enemies; i++){
    	if (enemies[i]->get_position()==removableEnemy->get_position()){
    		enemies.erase(enemies.begin()+i);
    	}
    }
	delete removableEnemy;
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
    for (unsigned int i=0; i<enemies.size(); i++){
        enemies[i]->updateFrame();
    }
    player.updateShots();
    for (auto& door : doors){
        door.updateFrame();
    }

    for (unsigned int i=0; i<explosions.size(); i++){
        SpriteHolder* explosion = explosions[i];
        explosion->updateExplosion();
        if (explosion->explosionComplete() and !explosion->hasTextures()){ //Si terminé la animacion de explosion y no almacena otro sprite, lo borro
            unsigned int j=0;
            bool founded = false;
            Coordinates explosion_pos = explosion->get_position();
            while(j<sprites.size() and !founded){
                Coordinates sprites_pos = sprites[j]->get_position();
                if (explosion_pos==sprites_pos){
                    map.removePositionable(explosion->get_position());
                    explosions.erase(explosions.begin() + i);
                    sprites.erase(sprites.begin() + j);
                    delete explosion;
                }
                j++;
            }
        }
    }  
}

void GameModelClient::showWindow(){
    window.showWindow();
}

void GameModelClient::hideWindow(){
    window.hideWindow();
}

ClientMap& GameModelClient::getMap(){
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

void GameModelClient::addSpriteOn(Coordinates position, int sprite_value, bool add_explosion){
  bool position_has_sprite_already = false;
  int cant_sprites = sprites.size();
  int i=0;
    while (i<cant_sprites and !position_has_sprite_already){
        if (sprites[i]->get_position()==position){
            position_has_sprite_already=true;
            if (add_explosion){
                sprites[i]->addExplosion();
                explosions.push_back(sprites[i]);
            }else{
                sprites[i]->addSprite(sprite_value);
            }
        }
        i++;
    }
    if (!position_has_sprite_already){
        bool position_has_door = false;
        i=0;
        int cant_doors = doors.size();
        while(i<cant_doors){
            if (doors[i].get_position()==position){
                position_has_door = true;
            }
            i++;
        }
        if (!position_has_door){
            SpriteHolder *posicionable = 
                new SpriteHolder(position,player);
            if (add_explosion){
                posicionable->addExplosion();
                explosions.push_back(posicionable);
            }else{
                posicionable->addSprite(sprite_value);
            }
            posicionable->set_texture(&texture);
            sprites.push_back(posicionable);  
            map.addPositionable(posicionable,position);  
        }
    }
}

void GameModelClient::addDeadSprite(Coordinates position, 
        CharacterType character_type){
  //printf("El personaje muerto es: %i \n", a_character_type);
    if (character_type==dog){
        addSpriteOn(position,texture_values.at("dead_dog"), false); 
    } else if (character_type==guard){
        addSpriteOn(position,texture_values.at("dead_guard"), false);
    } else if (character_type==officer){
        addSpriteOn(position,texture_values.at("dead_officer"), false);
    } else if (character_type==ss){
        addSpriteOn(position,texture_values.at("dead_ss"), false);
    } else {
        addSpriteOn(position,texture_values.at("dead_mutant"), false);
    }
}

void GameModelClient::removeCharacterFromMap(int id){
    Character* removableCharacter = characters[id];
    Coordinates removablePosition = removableCharacter->get_position();
    map.removeMovable(removablePosition);
}

void GameModelClient::processProtocol(Protocol& protocol){
    std::cout << "protocolo:\n";
    std::cout << protocol.getAction() << std::endl;
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
            CharacterType character_type = character->getType();
            Coordinates position = character->getPosicion();
            removeCharacterFromMap(protocol.getId());
            addDeadSprite(position,character_type);
            playSound(SoundPlayer::sound_type::DYING, character);
            if(character->getId()==player.getId()){
                player.removeLive();
                if(!player.hasLivesLeft()){
                    player_alive=false;
                }
            }
            break;
        }
        case Protocol::action::RESURRECT:{
            auto character = characters.at(protocol.getId());
            Coordinates res_pos(protocol.getPosition());
            character->resurrect(res_pos);
            break;
        }
        case Protocol::action::REMOVE:
            removeEnemy(protocol.getUserId());
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
            _have_winner = true;
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
    } else{
        Character* character= characters[protocol.getId()];
        Enemy* enemy = static_cast<Enemy*>(character);
        float distance = calculateDistanceBetween(enemy);
        enemy->shoot(_sound_player, distance);
    }
}

void GameModelClient::processShooted(Protocol protocol){
    player.updateHealth(protocol.getDamage());
}

void GameModelClient::processPickup(Protocol& protocol){ //Ver bien este
    Coordinates position(protocol.getPosition());
    SpriteHolder* sprite = static_cast<SpriteHolder*>
        (map.getPositionableIn(position));
    if (sprite->hasCharacter()){
      Movable* character = sprite->getCharacter();
      map.removeSpriteWithCharacter(position,character);
    } else{
      map.removePositionable(position);
    }
}

void GameModelClient::processThrow(Protocol& protocol){
    Coordinates position(protocol.getPosition());
    position.x+=0.5;
    position.y+=0.5;
    SpriteHolder *posicionable = new 
        SpriteHolder(position,player);
    posicionable->addSprite(protocol.getId());
    posicionable->set_texture(&texture);
    sprites.push_back(posicionable);
    map.addPositionable(posicionable,position);
}

void GameModelClient::processGunSwitch(Protocol& protocol){
    if (protagonist_id == protocol.getId()){
        player.newGunType(protocol.getDamage());
    } else{
        Character* character= characters[protocol.getId()];
        Enemy* enemy = static_cast<Enemy*>(character);
        enemy->newEnemyType(protocol.getDamage());
    }
}

void GameModelClient::processRocket(Protocol& protocol){
    //Por ahora pruebo con un solo rocket
    //Coordinates position(protocol.getFloatPosition());
    int rocket_id = protocol.getRocketId();
    if (protocol.getAction() == Protocol::action::MOVE_ROCKET){
        //printf("x cambiarle la posicion, supuestamente está en: 
        // (%f,%f)\n",position.x,position.y);
        bool found = false;
        unsigned int i = 0;
        while (i<rockets.size() and !found){
            Rocket* rocket = rockets[i];
            //printf("Pero en realidad está en: (%f,%f)\n",
            // rocket->getPosicion().x,rocket->getPosicion().y );
            //if (position==rocket->getPosicion()){
            if (rocket->getRocketId()==rocket_id){
                found = true;
                rocket->move();
                //printf("le cambie la posicion, ahora es: 
                // (%f,%f)\n\n",rocket->getPosicion().x,
                // rocket->getPosicion().y);
            }
            i++;
        }
    } else{ //Creo el misil
        Coordinates direction = characters[protocol.getId()]->getDirection();
        Coordinates position = characters[protocol.getId()]->getPosicion();
        
        Coordinates new_pos = position;
        while (position == new_pos){
            new_pos.increment_on_direction(direction, 0.5);
        }
        Rocket* rocket = new Rocket(new_pos, direction, map, player, rocket_id);
        rocket->set_texture(&texture);
        rockets.push_back(rocket);
        map.addMovable(rocket,new_pos);
        //printf("cree uno nuevo en: (%f,%f)\n\n", position.x,position.y);
    }
}

void GameModelClient::processExplosion(Protocol& protocol){
    int rocket_id = protocol.getRocketId();
    bool found = false;
    unsigned int i = 0;
    //printf("posicion recibida: (%f,%f)\n",position.x,position.y);
    while (i<rockets.size() and !found){
        Rocket* rocket = rockets[i];
        //Coordinates rocket_position = rocket->getPosicion();
        //printf("posicion de mi rockett: (%f,%f)\n",rocket_position.x,
        //    rocket_position.y);
        //printf("Pero en realidad está en: (%f,%f)\n",rocket->getPosicion().
        //x,rocket->getPosicion().y );
        if (rocket->getRocketId()==rocket_id){
            Coordinates rocket_position = rocket->getPosicion();
            printf("aa\n");
            found = true;
            playSound(SoundPlayer::sound_type::ROCKET_EXPLOTION, rocket);
            map.removeMovable(rocket_position);
            rockets.erase(rockets.begin() + i);
            delete rocket;
            addSpriteOn(rocket_position,0, true);
            //printf("le cambie la posicion, ahora es: (%f,%f)\n\n",
                //rocket->getPosicion().x,rocket->getPosicion().y);
        }
        i++;
    }
    //auto rocket_pos = rockets[0]->get_position();
    //map.removePositionable(rocketsd[0]->get_position());
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
    setDoorState(door_pos,open);
}

void GameModelClient::setDoorState(Coordinates door_pos, State new_state){
    int cant_doors = doors.size();
    int i=0;
    bool founded = false;
    while (i<cant_doors and !founded){
        if (door_pos == doors[i].get_position()){
            founded = true;
            doors[i].setState(new_state);
        }
        i++;
    }
}

void GameModelClient::openingDoor(const Protocol& protocol){
    Coordinates door_pos(protocol.getPosition());
    setDoorState(door_pos,opening);
    playSound(SoundPlayer::sound_type::DOOR_OPENING, 
        map.getPositionableIn(door_pos));
}

void GameModelClient::closeDoor(const Protocol& protocol){
    Coordinates door_pos(protocol.getPosition());
    setDoorState(door_pos,closed);
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

void GameModelClient::playSound(SoundPlayer::sound_type sound_type, 
        Posicionable* positionable){
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
	for (auto& enemie : enemies){
		delete enemie;
	}

	for (auto& sprite : sprites){
		delete sprite;
	}

    for (auto& rocket : rockets){
        delete rocket;
    }

}
