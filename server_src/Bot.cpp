#include "Bot.h"

#include "Objeto.h"
#include "Mapa.h"
#include "Player.h"
#include "AtomicCoordinates.h"
#include <string>
#include <iostream>



enum Posicion{
	Vacio = 0,
	Ocupado ,
	Puerta 
};


void checkLua(lua_State *L, int r){
	if (r != LUA_OK){
		std::string errormsg = lua_tostring(L, -1);
		throw std::runtime_error(errormsg);
	}
}


int Bot::luaObtenerObjetoMapa(lua_State *L){
	if (lua_gettop(L) != 3) return -1;
	Bot* bot = static_cast<Bot*>(lua_touserdata(L,1));
	int x = (int)lua_tonumber(L, 2);
	int y = (int)lua_tonumber(L, 3);
	
	if (!bot->mapa.hayObstaculoEn(Coordinates(x, y))){
		lua_pushnumber(L, Posicion::Vacio);
	} else if (bot->mapa.hayPuertaEn(x, y)){
		lua_pushnumber(L, Posicion::Puerta);
	} else {
		lua_pushnumber(L, Posicion::Ocupado);
	}	
	return 1;
}


Bot::Bot(const Mapa& mapa): mapa(mapa){
	this->script = luaL_newstate();
	luaL_openlibs(this->script);
	lua_register(this->script, "obtenerObjetoMapa", luaObtenerObjetoMapa);
	checkLua(this->script,luaL_dofile(this->script,"../data/bot/bot.lua"));
    cargarMapa();
}

void Bot::cargarMapa(){
	lua_getfield(this->script, -1, "cargarMapa");
	if (!lua_isfunction(this->script, -1))
		throw std::runtime_error("Lua no pudo cargar mapa\n");
	lua_pushlightuserdata(this->script, this);
	lua_pushnumber(this->script, mapa.getAncho());
	lua_pushnumber(this->script, mapa.getAlto());
	lua_pcall(this->script, 3, 0, 0);	
}


Bot::Event Bot::getEvent(Player* jugador, std::map<int, Player*>& enemigos){
	lua_getfield(this->script, -1, "generarEvento");
	if (!lua_isfunction(this->script, -1))
		throw std::runtime_error("Lua no pudo generar un evento\n");
	
	int argc = pushInfoJugador(jugador);
	argc += pushInfoEnemigos(jugador, enemigos);

	lua_pcall(this->script, argc, 1, 0);
	Bot::Event evento = (Bot::Event) lua_tonumber(this->script, -1);
	lua_pop(this->script, 1);
	return evento;
}


int Bot::pushInfoJugador(Player* jugador){
	AtomicCoordinates& posicion = jugador->getAtomicPosition();
	AtomicCoordinates& direccion = jugador->getAtomicDirection();
	lua_pushnumber(this->script, jugador->numeroArmaActual());
	lua_pushnumber(this->script, posicion.x);
	lua_pushnumber(this->script, posicion.y);
	lua_pushnumber(this->script, direccion.x);
	lua_pushnumber(this->script, direccion.y);	
	return 5;
}


int Bot::pushInfoEnemigos(Player* j, std::map<int, Player*>& enemigos){
    int argc = 0;
    for (auto it = enemigos.begin(); it != enemigos.end(); ++it){
        auto* enemigo = it->second;
        if (enemigo != j){
            AtomicCoordinates& position = enemigo->getAtomicPosition();
            lua_pushnumber(this->script, position.x);
            lua_pushnumber(this->script, position.y);
            argc += 2;
        }
    }
    return argc;
}


Bot::~Bot(){
	lua_close(this->script);
}

