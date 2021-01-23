#include "Objeto.h"

#include <ConfigVariable.h>
class Mapa;
#include "Mapa.h"
#include "ThGameModelServer.h"

#define ROCKET_STEP 0.15
#define STEP 1


Coordinates& Objeto::getCoordinates(){
    return this->posicion;
}


ParedFalsa::ParedFalsa(Coordinates coordenadas): Objeto(coordenadas) {
    posicion.x += 0.5;  // Para estar en el centro de la posicion
    posicion.y += 0.5;  // Para estar en el centro de la posicion
}
bool ParedFalsa::abrir(Player *jugador){
    double angle = jugador->get_coordinates().calculate_angle(
        jugador->get_direction(), posicion);
    return (angle < 1);
}


Puerta::Puerta(Coordinates coordenadas): Objeto(coordenadas) {
    posicion.x += 0.5;  // Para estar en el centro de la posicion
    posicion.y += 0.5;  // Para estar en el centro de la posicion
}

bool Puerta::abrir(Player *jugador){
    return abrirPuerta(jugador);
}

bool Puerta::abrirPuerta(Player *jugador){
    double angle = jugador->get_coordinates().calculate_angle(
        jugador->get_direction(), posicion);
    if (angle < 1){
        atravesable(true);
        return true;
    }
    return false;
}

void Puerta::cerrar(){
	atravesable(false);
}


bool PuertaCerrada::abrir(Player *jugador){
	if (this->llave || jugador->usarLlave())
		return abrirPuerta(jugador);
    return false;
}
	
    

Rocket::Rocket(Coordinates position, Coordinates dir,
    Player* player, std::map<int, Player*>& enemies,
    ThGameModelServer& game_model):
    Objeto(position), position(position), direction(dir),
    player(player), enemies(enemies), map(player->getMapa()){
    exploded = false;
    map.agregarPosicionable(this, position);
    //echo protocol
}

void Rocket::move(ThGameModelServer& game_model){
    map.sacarPosicionable(position, typeid(this));
    // Protocol sacar objeto mapa
    position.increment_on_direction(direction, ROCKET_STEP);
    if (map.hayObstaculoEn(position)){
        return explode();
    }
    map.agregarPosicionable(this, position);
    // Protocol agregar objeto mapa
}

void Rocket::explode(){
    for (auto it = enemies.begin(); it != enemies.end(); ++it){
        auto* enemy = it->second;
        double distancia = position.calculate_distance(
			enemy->get_coordinates());

        if (distancia > (int)configs[CONFIG::distancia_explosion_cohete])
            continue;
        if (colisionaConObjeto(position, enemy->get_coordinates()))
            continue;
			
        float damage = (int)configs[CONFIG::maximo_danio] * 
        (1 - distancia /(int)configs[CONFIG::distancia_explosion_cohete]);
        bool is_dead = enemy->recibirDanio(std::ceil(damage));
        if (is_dead)
            player->agregarEnemigoMuerto();
    }
    exploded = true;
}

bool Rocket::hasExploded(){
    return exploded;
}

bool Rocket::colisionaConObjeto(const Coordinates& inicio, 
    const Coordinates& fin){
	if (inicio == fin) return false;
	Coordinates direccion(fin.x - inicio.x, fin.y - inicio.y);
	Coordinates actual(inicio.x, inicio.y);
	direccion.normalice_direction();
	actual.increment_on_direction(direccion, STEP);

	while (actual != fin){
		if (map.hayObstaculoEn(actual) && actual != inicio)
			return true;
		actual.increment_on_direction(direccion, STEP);
	}
	return false;
}

Rocket::~Rocket(){
}	
