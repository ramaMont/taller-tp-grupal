#include "ServerMap.h"

#include "Event.h"
#include <ConfigVariable.h>
#include "EnvVariablesGetter.h"

#include <iostream>
#include <utility>
#include <cmath>
#include <typeinfo>
#include <yaml-cpp/yaml.h>
#include <string>
#include <vector>
#include <map>
#include <tuple>


// Codigo de errores en int (despues cambiar a excepciones)
// -1 lugar no encontrado
// -2 lugar ocupado

void ServerMap::initMap(ServerMap& map, YAML::Node map_node){
    std::string pos="pos_";
    for (int i=0; i<alto; i++){
        for (int j=0; j<ancho; j++){
            std::string actual_position = pos + std::to_string(i) + "_" +
                std::to_string(j);
            std::string elemento = map_node[actual_position].as<std::string>();
            std::string parsed_element;
            try{
                parsed_element = elemento.substr(0,5);
            } catch(...){
                parsed_element = elemento;
            }
            if (parsed_element == "wall_"){
                Coordinates position((float)i,(float)j);
                Posicionable* posicionable = new Posicionable(position);
                map.addPosicionable(posicionable,position);
            } else if (parsed_element == "door"){
                Coordinates position((float)i,(float)j);
                Door* posicionable = new Door(position);
                map.addPassage(posicionable);
            } else if (parsed_element == "playe"){
                std::string dir_str = elemento.substr(7, elemento.size() - 5);
                Coordinates position((float)i,(float)j);
                std::tuple<Coordinates, std::string> player_data = 
                    std::make_tuple(position, dir_str);
                player_positions.push_back(player_data);
            } else if (elemento == "empty"){
                // No hace falta hacer nada.
            } else if (elemento == "key_door"){
                Coordinates position((float)i,(float)j);
                KeyDoor* posicionable = new KeyDoor(position);
                map.addPassage(posicionable);
            } else if (elemento.substr(0,7) == "passage"){
                Coordinates position((float)i,(float)j);
                Passage* posicionable = new Passage(position);
                map.addPassage(posicionable);
            } else if (elemento == "food"){
                Coordinates position((float)i,(float)j);
                Food* posicionable = new Food(position);
                map.addItem(posicionable, position);
            } else if (elemento == "medicine"){
                Coordinates position((float)i,(float)j);
                Medicine* posicionable = new Medicine(position);
                map.addItem(posicionable, position);
            } else if (elemento == "blood"){
                Coordinates position((float)i,(float)j);
                Blood* posicionable = new Blood(position);
                map.addItem(posicionable, position);
            } else if (elemento == "bullets"){
                Coordinates position((float)i,(float)j);
                Bullets* posicionable = new Bullets(position);
                map.addItem(posicionable, position);
            } else if (elemento == "key"){
                Coordinates position((float)i,(float)j);
                Key* posicionable = new Key(position);
                map.addItem(posicionable, position);
            } else if (elemento == "cross__"){   // cross
                Coordinates position((float)i,(float)j);
                Cross* posicionable = new Cross(position);
                map.addItem(posicionable, position);
            } else if (elemento == "trophie"){
                Coordinates position((float)i,(float)j);
                Trophie* posicionable = new Trophie(position);
                map.addItem(posicionable, position);
            } else if (elemento == "chest__"){    //
                Coordinates position((float)i,(float)j);
                Chest* posicionable = new Chest(position);
                map.addItem(posicionable, position);
            } else if (elemento == "crown__"){    //
                Coordinates position((float)i,(float)j);
                Crown* posicionable = new Crown(position);
                map.addItem(posicionable, position);
            } else if (elemento == "machine_gun"){
                Coordinates position((float)i,(float)j);
                MachineGun* posicionable = new MachineGun(position);
                map.addItem(posicionable, position);
            } else if (elemento == "fire_canon"){
                Coordinates position((float)i,(float)j);
                FireCanon* posicionable = new FireCanon(position);
                map.addItem(posicionable, position);
            } else if (elemento == "rocket_launcher"){
                Coordinates position((float)i,(float)j);
                RocketLauncher* posicionable = \
                    new RocketLauncher(position);
                map.addItem(posicionable, position);
            } else if (elemento == "barrel" || elemento == "pillar" ||
                       elemento == "table"){
                Coordinates position((float)i,(float)j);
                Posicionable* posicionable = new Posicionable(position);
                map.addPosicionable(posicionable, position);
            }
        }
    }
}

ServerMap::ServerMap(const std::string& map_filename): players_added(0){
    EnvVariablesGetter envVariablesGetter;
    std::string MAPS_PATH = envVariablesGetter.getMapsPath();
    YAML::Node map_node = YAML::LoadFile(MAPS_PATH + map_filename);
    alto = map_node["filas"].as<int>();
    ancho = map_node["columnas"].as<int>();
    mapaJuego.resize(alto, std::vector<std::vector<Posicionable*>>(ancho));
    items.resize(alto, std::vector<Item*>(ancho));
    initItems();
    initMap(*this, map_node["elementos"]);
}

void ServerMap::initItems(){
    for (int x = 0; x < alto; ++x){
        for (int y = 0; y < ancho; ++y){
            items[x][y] = nullptr;
        }
    }
}

void ServerMap::addPlayer(Player* player){
    if (players_added >= (int)player_positions.size())
        throw -1; // Se quiere agregar un jugador mas a una partida completa
    auto player_data = player_positions.at(players_added);
    auto player_position = std::get<0>(player_data);
    auto player_dir = std::get<1>(player_data);
    player->setPosition(player_position);
    player->set_direction(player_dir);
	mapaJuego[floor(player_position.x)][floor(player_position.y)].
        push_back(player);
    ++players_added;
}

void ServerMap::respawnPlayer(Player* player){
    Coordinates player_position = player->get_position();
	mapaJuego[floor(player_position.x)][floor(player_position.y)].
        push_back(player);
}

void ServerMap::addPosicionable(Posicionable* posicionable, 
        Coordinates posicion){
	if (floor(posicion.x) < 0 || floor(posicion.x) >= alto ||
	    floor(posicion.y) < 0 || floor(posicion.y) >= ancho) return;
	if(mapaJuego[floor(posicion.x)][floor(posicion.y)].empty()){
		mapaJuego[floor(posicion.x)][floor(posicion.y)].
            push_back(posicionable);
	}else{
		std::vector<Posicionable*>& vec = 
		    mapaJuego[floor(posicion.x)][floor(posicion.y)];
		if (!vec.back() || vec.back()->atravesable()){
			vec.push_back(posicionable);
            return;
		}
        if (typeid(*vec.back()) == typeid(Rocket))
            static_cast<Rocket*>(vec.back())->explode(true);
        throw -2;//Quiero guardar algo donde ya hay otra cosa
	}
}

void ServerMap::addItem(Item* item, Coordinates posicion){
	if (floor(posicion.x) < 0 || floor(posicion.x) >= alto ||
	    floor(posicion.y) < 0 || floor(posicion.y) >= ancho) return;
	if (items[floor(posicion.x)][floor(posicion.y)] == nullptr)
        items[floor(posicion.x)][floor(posicion.y)] = item;
}

Coordinates ServerMap::getEmptyPosition(const Coordinates& posicion){
    int pos_x = floor(posicion.x);
    int pos_y = floor(posicion.y);
    for (int i = 1; i < 5; ++i){
        for (int x = pos_x - i; x <= pos_x + i; ++x){
            if (x < 0 || x >= alto) continue;
            for (int y = pos_y - i; y <= pos_y + i; ++y){
                 if (y < 0 || y >= ancho) continue;
                 if (items[x][y] || !mapaJuego[x][y].empty()) continue;
                 return Coordinates(x, y);
            }
        }
    }
    return Coordinates(-1, -1);
}

void ServerMap::addPassage(Object* door){
    passages.push_back(door);
    addPosicionable(door, door->getPosicion());
}

void ServerMap::removePosicionable(const Coordinates& posicion){
    if (!mapaJuego[floor(posicion.x)][floor(posicion.y)].empty())
	    mapaJuego[floor(posicion.x)][floor(posicion.y)].pop_back();
}
    
void ServerMap::removeItem(const Coordinates& posicion){
    if (items[floor(posicion.x)][floor(posicion.y)]){
        delete(items[floor(posicion.x)][floor(posicion.y)]);
        items[floor(posicion.x)][floor(posicion.y)] = nullptr;
    }
}

void ServerMap::removePassage(const Coordinates& position){
    removePosicionable(position);
    for (auto it = passages.begin(); it < passages.end(); ++it){
        if ((*it)->getPosicion() == position){
            passages.erase(it);
            return;
        }
    }
}


Posicionable* ServerMap::getPosicionableIn(Coordinates posicion) const{
	if (floor(posicion.x) < 0 || floor(posicion.x) >= alto ||
	    floor(posicion.y) < 0 || floor(posicion.y) >= ancho) return nullptr;
	if (mapaJuego[floor(posicion.x)][floor(posicion.y)].empty())
		return nullptr;
	return mapaJuego[floor(posicion.x)][floor(posicion.y)].back();
}

Object* ServerMap::getNearestPassage(Coordinates& position){
    Object* nearest = nullptr;
    float min_distance = configs[CONFIG::open_distance];
    for (Object* passage: passages){
        float dist = position.calculate_distance(passage->getPosicion());
        if (dist < min_distance){
            min_distance = dist;
            nearest = passage;
        }
    }
    return nearest;
}

Door* ServerMap::getDoor(const Coordinates& position){
    for (Object* passage: passages){
        if (passage->getPosicion() == position &&    \
                (typeid(*passage) == typeid(Door) || \
                typeid(*passage) == typeid(KeyDoor))){
            return static_cast<Door*>(passage);
        }
    }
    return nullptr;
} 

void ServerMap::moveme(Player* player, const Coordinates& posicion){
    if (floor(posicion.x) >= alto || floor(posicion.y) >= ancho)
        throw -1;
    if (floor(posicion.x) < 0 || floor(posicion.y) < 0)
        throw -1;
    Coordinates posPlayer = player->getPosicion();
    if (posPlayer == posicion){
        return;
    }
    try {
        addPosicionable(player, posicion);
        if (items[floor(posicion.x)][floor(posicion.y)])
            player->use(items[floor(posicion.x)][floor(posicion.y)]);
        removePosicionable(posPlayer);
    } catch(int e){
        throw;
    }
}

ServerMap::ServerMap(ServerMap&& other){
    this->alto = other.alto;
    this->ancho = other.ancho;
    this->mapaJuego.swap(other.mapaJuego);
    this->players_added = other.players_added;
}

ServerMap& ServerMap::operator=(ServerMap&& other){
    if (this == &other){
        return *this;        // other is myself!
    }
    this->alto = other.alto;
    this->ancho = other.ancho;
    this->mapaJuego.swap(other.mapaJuego);
    this->players_added = other.players_added;
    return *this;
}

bool ServerMap::obstacleIn(const Coordinates& posicion) const{
	float x = posicion.x;
	float y = posicion.y;
	if (floor(x) < 0 || floor(x) >= alto ||
	    floor(y) < 0 || floor(y) >= ancho) return true;
	if (mapaJuego[floor(x)][floor(y)].empty())
		return false;
	if (mapaJuego[floor(x)][floor(y)].back()->atravesable() ||
        typeid(*mapaJuego[floor(x)][floor(y)].back()) == typeid(Player))
		return false;
	return true;
}

bool ServerMap::playerIn(const Coordinates& posicion) const{
	if (floor(posicion.x) < 0 || floor(posicion.x) >= alto ||
	    floor(posicion.y) < 0 || floor(posicion.y) >= ancho) return true;
	return (!mapaJuego[floor(posicion.x)][floor(posicion.y)].empty() && 
	typeid(*mapaJuego[floor(posicion.x)][floor(posicion.y)].back()) == 
        typeid(Player));
}

bool ServerMap::doorIn(float x, float y) const{
	if (floor(x) < 0 || floor(x) >= alto ||
	    floor(y) < 0 || floor(y) >= ancho ||
	    mapaJuego[floor(x)][floor(y)].empty()) return false;
	return (typeid(*mapaJuego[floor(x)][floor(y)].back()) == typeid(Door) ||
            typeid(*mapaJuego[floor(x)][floor(y)].back()) == typeid(KeyDoor));
}

int ServerMap::getAlto() const{
	return this->alto;
}

int ServerMap::getAncho() const{
	return this->ancho;
}

// Se encarga de limpiar los vectores con usuarios y jugadores.
ServerMap::~ServerMap(){
    for (int i = 0; i < alto; ++i){
        for (int j = 0; j < ancho; ++j){
            for (Posicionable* p: mapaJuego[i][j]){
                delete(p);
            }
            if (items[i][j])
                delete(items[i][j]);
        }
    }
}
