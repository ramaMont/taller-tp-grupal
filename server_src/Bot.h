#ifndef __BOT_H__
#define __BOT_H__

#include "Mapa.h"
#include <vector>

extern "C"{
	#include "lua/include/lua.h"
	#include "lua/include/lauxlib.h"
	#include "lua/include/lualib.h"
}


enum Evento{
	MoverAdelante = 0,
	MoverIzquierda,
	MoverDerecha,
	Disparar,
	CambiarArmaCuchillo,
	AbrirPuerta
};


class Bot{
	private:
	lua_State* script;
	const Mapa& mapa;
	
	public:
	Bot(const Mapa& mapa);
    void cargarMapa();
	int getEvent(const Jugador* jugador, const std::vector<Jugador*>& enemigos);
	static int luaObtenerObjetoMapa(lua_State *L);
	int pushInfoJugador(const Jugador* jugador);
	int pushInfoEnemigos(const Jugador* j, const std::vector<Jugador*>& enemigos);
	~Bot();
};

#endif
