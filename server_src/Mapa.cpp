#include "Mapa.h"
#include <iostream>
#include <utility>
#include <cmath>
#include <typeinfo>
#include "Objeto.h"
#include "Event.h"
#include <ConfigVariable.h>

#include <yaml-cpp/yaml.h>
#include <string>


// Codigo de errores en int (despues cambiar a excepciones)
// -1 lugar no encontrado
// -2 lugar ocupado
// Pongo esta funcion global horrible aca, para inicializar los mapas de 
// manera momentanea.
// void initMap(Mapa& map){
//     std::vector<std::vector<int>> a_map{
//         {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//         {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//         {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//         {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//         {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
//     };
//     for (int i=0; i<24; i++){
//         for (int j=0; j<24; j++){
//             if (a_map[i][j]!=0){
//                 Coordinates position((float)i,(float)j);
//                 Posicionable* posicionable = new Posicionable(position);
//                 map.agregarPosicionable(posicionable,position);
//             }
//         }
//     }
// }

void Mapa::initMap(Mapa& map, YAML::Node map_node){
    std::string position="pos_";
    for (int i=0; i<alto; i++){
        for (int j=0; j<ancho; j++){
            std::string actual_position = position + std::to_string(i) + "_" +
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
                map.agregarPosicionable(posicionable,position);
            } else if (parsed_element == "door"){
                Coordinates position((float)i,(float)j);
<<<<<<< HEAD
                Posicionable* posicionable = new Puerta(position);
                map.agregarPosicionable(posicionable,position);
            } else if (parsed_element == "empty"){
=======
                Puerta* posicionable = new Puerta(position);
                map.addDoor(posicionable);
            } else if (elemento == "vacio"){
>>>>>>> c9d566e9fdff59aec9b57db9a877573546008ddc
                // No hace falta hacer nada.
            }
        }
    }
}

Mapa::Mapa(std::string map_filename){
	std::string MAPS_PATH = "../data/maps/";
    YAML::Node map_node = YAML::LoadFile(MAPS_PATH + map_filename);
    alto = map_node["filas"].as<int>();
    ancho = map_node["columnas"].as<int>();
    mapaJuego.resize(ancho, std::vector<std::vector<Posicionable*>>(alto));
    items.resize(ancho, std::vector<std::vector<Item*>>(alto));
    initMap(*this, map_node["elementos"]);
}

Mapa::Mapa(int alto, int ancho):alto(alto), ancho(ancho),mapaJuego(ancho,
        std::vector<std::vector<Posicionable*>>(alto)),
        items(ancho, std::vector<std::vector<Item*>>(alto)){
    /*for (int i=0; i<ancho; i++){
        for (int j=0; j<alto; j++){
            mapaJuego[i][j]=nullptr;
        }
    }*/
}

void Mapa::agregarPlayer(Player* jugador){
	const Coordinates& posicion = jugador->getPosicion();
	mapaJuego[floor(posicion.x)][floor(posicion.y)].push_back(jugador);
}

void Mapa::agregarPosicionable(Posicionable* posicionable, 
        Coordinates posicion){
	if (floor(posicion.x) < 0 || floor(posicion.x) >= ancho ||
	    floor(posicion.y) < 0 || floor(posicion.y) >= alto) return;
	if(mapaJuego[floor(posicion.x)][floor(posicion.y)].empty()){
		mapaJuego[floor(posicion.x)][floor(posicion.y)].push_back(posicionable);
	}else{
		std::vector<Posicionable*>& vec = 
		    mapaJuego[floor(posicion.x)][floor(posicion.y)];
		if (!vec.back() || vec.back()->atravesable()){
			vec.push_back(posicionable);
		}else{
			throw -2;//Quiero guardar algo donde ya hay otra cosa
		}
	}
}

void Mapa::agregarItem(Item* item, Coordinates posicion){
	if (floor(posicion.x) < 0 || floor(posicion.x) >= ancho ||
	    floor(posicion.y) < 0 || floor(posicion.y) >= alto) return;
	items[floor(posicion.x)][floor(posicion.y)].push_back(item);
}

void Mapa::addDoor(Puerta* door){
    doors.push_back(door);
    agregarPosicionable(door, door->getCoordinates());
}

void Mapa::sacarPosicionable(Coordinates posicion){
    if (!mapaJuego[floor(posicion.x)][floor(posicion.y)].empty())
	    mapaJuego[floor(posicion.x)][floor(posicion.y)].pop_back();
}

void Mapa::sacarItem(Coordinates posicion, const std::type_info& type_id){
    std::vector<Item*>& vec = items[floor(posicion.x)][floor(posicion.y)];
    for (auto it = vec.begin(); it < vec.end(); ++it){
        if (typeid(*it) == type_id){
            delete(*it);
            vec.erase(it);
            return;
        }
    }
}

Posicionable* Mapa::obtenerPosicionableEn(Coordinates posicion) const{
	if (floor(posicion.x) < 0 || floor(posicion.x) >= ancho ||
	    floor(posicion.y) < 0 || floor(posicion.y) >= alto) return nullptr;
	if (mapaJuego[floor(posicion.x)][floor(posicion.y)].empty())
		return nullptr;
	return mapaJuego[floor(posicion.x)][floor(posicion.y)].back();
}

Objeto* Mapa::getNearestDoor(Coordinates& position){
    Objeto* nearest = nullptr;
    float min_distance = configs[CONFIG::open_distance];
    for (Objeto* door: doors){
        float dist = position.calculate_distance(door->getCoordinates());
        if (dist < min_distance){
            min_distance = dist;
            nearest = door;
        }
    }
    return nearest;
}

void usarItems(std::vector<Item*>& items, Player *player){
    for (auto it = items.begin(); it < items.end(); it++){
        (*it)->usar(player);
    }
}

void Mapa::moveme(Player* jugador, const Coordinates& posicion){
    if (floor(posicion.x) >= ancho || floor(posicion.y) >= alto)
        throw -1;
    if (floor(posicion.x) < 0 || floor(posicion.y) < 0)
        throw -1;
    Coordinates posJugador = jugador->getPosicion();
    if (jugador->getPosicion() == posicion){
        return;
    }
    try {
        if (!items[floor(posicion.x)][floor(posicion.y)].empty())
            usarItems(items[floor(posicion.x)][floor(posicion.y)], jugador);
        agregarPosicionable(jugador, posicion);
        sacarPosicionable(posJugador);
    } catch(int e){
        throw;
    }
}

Mapa::Mapa(Mapa&& other){
    this->alto = other.alto;
    this->ancho = other.ancho;
    this->mapaJuego.swap(other.mapaJuego);
}

Mapa& Mapa::operator=(Mapa&& other){
    if (this == &other){
        return *this;        // other is myself!
    }
    this->alto = other.alto;
    this->ancho = other.ancho;
    this->mapaJuego.swap(other.mapaJuego);
    return *this;
}

bool Mapa::hayObstaculoEn(const Coordinates& posicion) const{
	return hayObstaculoEn(posicion.x, posicion.y);
}

bool Mapa::hayObstaculoEn(float x, float y) const{
	if (floor(x) < 0 || floor(x) >= ancho ||
	    floor(y) < 0 || floor(y) >= alto) return true;
	if (mapaJuego[floor(x)][floor(y)].empty())
		return false;
	if (mapaJuego[floor(x)][floor(y)].back()->atravesable())
		return false;
	return true;
}

bool Mapa::hayPuertaEn(float x, float y) const{
	if (floor(x) < 0 || floor(x) >= ancho ||
	    floor(y) < 0 || floor(y) >= alto ||
	    mapaJuego[floor(x)][floor(y)].empty()) return false;
	return typeid(*mapaJuego[floor(x)][floor(y)].back()) == typeid(Puerta);
}

bool Mapa::hayJugadorEn(float x, float y) const{
	if (floor(x) < 0 || floor(x) >= ancho ||
	    floor(y) < 0 || floor(y) >= alto ||
	    mapaJuego[floor(x)][floor(y)].empty()) return false;
	return typeid(*mapaJuego[floor(x)][floor(y)].back()) == typeid(Player);
}

int Mapa::getAlto() const{
	return this->alto;
}

int Mapa::getAncho() const{
	return this->ancho;
}

// Se encarga de limpiar los vectores con usuarios y jugadores.
Mapa::~Mapa(){
    for (int i = 0; i < alto; ++i){
        for (int j = 0; j < ancho; ++j){
            for (Posicionable* p: mapaJuego[i][j]){
                delete(p);
            }
            for (Item* i: items[i][j]){
                delete(i);
            }
        }
    }
}
