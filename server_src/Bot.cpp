#include "Bot.h"

#include "Objeto.h"
#include "Mapa.h"
#include "Player.h"
#include "AtomicCoordinates.h"
#include <string>
#include <iostream> //

#define PLAYER_ARGS 5

enum MapSpot{
	Empty = 0,
	Busy,
	Door
};


void checkLua(lua_State *L, int r){
	if (r != LUA_OK){
		std::string errormsg = lua_tostring(L, -1);
		throw std::runtime_error(errormsg);
	}
}


int Bot::luaGetMapObject(lua_State *L){
	if (lua_gettop(L) != 3) return -1;
	Bot* bot = static_cast<Bot*>(lua_touserdata(L,1));
	int x = (int)lua_tonumber(L, 2);
	int y = (int)lua_tonumber(L, 3);
	
	if (!bot->map.hayObstaculoEn(Coordinates(x, y))){
		lua_pushnumber(L, MapSpot::Empty);
	} else if (bot->map.hayPuertaEn(x, y)){
		lua_pushnumber(L, MapSpot::Door);
	} else {
		lua_pushnumber(L, MapSpot::Busy);
	}	
	return 1;
}


Bot::Bot(const Mapa& map): map(map){
	this->script = luaL_newstate();
	luaL_openlibs(this->script);
	lua_register(this->script, "getMapObject", luaGetMapObject);
	checkLua(this->script,luaL_dofile(this->script,"../data/bot/bot.lua"));
    loadMap();
}

void Bot::loadMap(){
	lua_getfield(this->script, -1, "loadMap");
	if (!lua_isfunction(this->script, -1))
		throw std::runtime_error("Lua no pudo cargar mapa\n");
	lua_pushlightuserdata(this->script, this);
	lua_pushnumber(this->script, map.getAncho());
	lua_pushnumber(this->script, map.getAlto());
	lua_pcall(this->script, 3, 0, 0);	
}


Bot::Event Bot::getEvent(Player* player, std::map<int, Player*>& enemies){
	lua_getfield(this->script, -1, "generarEvento");
	if (!lua_isfunction(this->script, -1))
		throw std::runtime_error("Lua no pudo generar un evento\n");
	
	int argc = pushInfoPlayer(player);
	argc += pushInfoEnemies(player, enemies);

	lua_pcall(this->script, argc, 1, 0);
	Bot::Event event = (Bot::Event) lua_tonumber(this->script, -1);
	lua_pop(this->script, 1);
	return event;
}


int Bot::pushInfoPlayer(Player* player){
	AtomicCoordinates& position = player->getAtomicPosition();
	AtomicCoordinates& direction = player->getAtomicDirection();
	lua_pushnumber(this->script, player->numeroArmaActual());
	lua_pushnumber(this->script, position.x);
	lua_pushnumber(this->script, position.y);
	lua_pushnumber(this->script, direction.x);
	lua_pushnumber(this->script, direction.y);	
	return PLAYER_ARGS;
}


int Bot::pushInfoEnemies(Player* j, std::map<int, Player*>& enemies){
    int argc = 0;
    for (auto it = enemies.begin(); it != enemies.end(); ++it){
        auto* enemy = it->second;
        if (enemy != j){
            AtomicCoordinates& position = enemy->getAtomicPosition();
            lua_pushnumber(this->script, position.x);
            argc ++;
            lua_pushnumber(this->script, position.y);
            argc ++;
        }
    }
    return argc;
}


Bot::~Bot(){
	lua_close(this->script);
}

