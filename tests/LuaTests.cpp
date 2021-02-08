#include "gtest/gtest.h"
#include "Mapa.h"
#include "Player.h"
#include "Bot.h"
#include "Posicionable.h"
#include "Object.h"
#include <vector>

/*
TEST(LuaTests, siTieneOtraArmaCambiaACuchillo) {
    //arrange
    Mapa mapa(10, 10);
    Bot bot(mapa);
    Jugador jugador(Coordinates(2,2), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    
    //act
	int evento = bot.getEvent(&jugador, vec);
	
	//assert
	EXPECT_EQ (evento, Evento::CambiarArmaCuchillo);
}

TEST(LuaTests, siEstaCruzandoUnaPueraAvanza) {
    //arrange
    Mapa mapa(10, 10);
    Puerta puerta(Coordinates(2,2));
    mapa.agregarPosicionable(&puerta, Coordinates(2,2));
    Bot bot(mapa);
    Jugador jugador(Coordinates(2,2), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    
    //act
	jugador.cambiarArma(0);
	int evento = bot.getEvent(&jugador, vec);
	
	//assert
	EXPECT_EQ (evento, Evento::MoverAdelante);
}

TEST(LuaTests, siTieneUnaPuertaAdelanteLaAbreUnaSolaVez) {
    //arrange
    Mapa mapa(10, 10);
    Puerta puerta(Coordinates(2,2));
    mapa.agregarPosicionable(&puerta, Coordinates(3,2));
    Bot bot(mapa);
    Jugador jugador(Coordinates(2,2), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    
    //act
	jugador.cambiarArma(0);
	int evento = bot.getEvent(&jugador, vec);
	//assert
	EXPECT_EQ (evento, Evento::AbrirPuerta);
    
    //act
	evento = bot.getEvent(&jugador, vec);
	//assert
	EXPECT_TRUE (evento != Evento::AbrirPuerta);
}

TEST(LuaTests, siTieneUnEnemigoAdelanteAtaca) {
    //arrange
    Mapa mapa(10, 10);
    Bot bot(mapa);
    Jugador jugador(Coordinates(3,3), Coordinates(-0.7, 0.7),  mapa);
    Jugador enemigo(Coordinates(2,4), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    
    //act
	jugador.cambiarArma(0);
	int evento = bot.getEvent(&jugador, vec);
	
	//assert
	EXPECT_EQ (evento, Evento::Disparar);
}

TEST(LuaTests, atacaADistancia1) {
    Mapa mapa(10, 10);
    Bot bot(mapa);
    Jugador jugador(Coordinates(5,5), Coordinates(0.99, 0),  mapa);
    Jugador enemigo1(Coordinates(7,5), Coordinates(1, 0),  mapa); // Distancia 2
    Jugador enemigo2(Coordinates(6,5), Coordinates(1, 0),  mapa); // Distancia 1
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo1);
    
	jugador.cambiarArma(0);
	int evento = bot.getEvent(&jugador, vec);
	EXPECT_EQ (evento, Evento::MoverAdelante); // Distancia 2
	
    vec.push_back(&enemigo2);
    EXPECT_EQ (bot.getEvent(&jugador, vec), Evento::Disparar);// Distancia1
}

TEST(LuaTests, siTieneUnEnemigoMasAdelanteAvanza) {
    //arrange
    Mapa mapa(10, 10);
    Bot bot(mapa);
    Jugador jugador(Coordinates(2,2), Coordinates(1, 0),  mapa);
    Jugador enemigo(Coordinates(5,2), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    
    //act
	jugador.cambiarArma(0);
	int evento = bot.getEvent(&jugador, vec);
	
	//assert
	EXPECT_EQ (evento, Evento::MoverAdelante);
}

TEST(LuaTests, siTieneUnEnemigoEnElCostadoGira) {
    //arrange
    Mapa mapa(10, 10);
    Bot bot(mapa);
    Jugador jugador(Coordinates(2,2), Coordinates(1, 0),  mapa);
    Jugador enemigo(Coordinates(1,2), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    
    //act
	jugador.cambiarArma(0);
	int evento = bot.getEvent(&jugador, vec);

	//assert
	EXPECT_TRUE (evento == Evento::MoverIzquierda ||
	             evento == Evento::MoverDerecha);
}

TEST(LuaTests, siNoPuedeAvanzarGira) {
    //arrange
    Mapa mapa(10, 10);
    Objeto pared(Coordinates(3,3));
    mapa.agregarPosicionable(&pared, Coordinates(3,2));
    Bot bot(mapa);
    Jugador jugador(Coordinates(2,2), Coordinates(1, 0),  mapa);
    Jugador enemigo(Coordinates(4,2), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    
    //act
	jugador.cambiarArma(0);
	int evento = bot.getEvent(&jugador, vec);
	
	//assert
	EXPECT_TRUE (evento == Evento::MoverIzquierda ||
	             evento == Evento::MoverDerecha);
}

TEST(LuaTests, giraCorrectoADerechaMirandoADerecha) {
    //arrange
    Mapa mapa(10, 10);
    Bot bot(mapa);
    Jugador jugador(Coordinates(5,5), Coordinates(1, 0),  mapa);
    Jugador enemigo(Coordinates(5,3), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    
    //act
	jugador.cambiarArma(0);
	int evento = bot.getEvent(&jugador, vec);
	
	//assert
	EXPECT_EQ (evento, Evento::MoverDerecha);
}

TEST(LuaTests, giraCorrectoADerechaMirandoAIzquierda) {
    //arrange
    Mapa mapa(10, 10);
    Bot bot(mapa);
    Jugador jugador(Coordinates(5,5), Coordinates(-1, 0),  mapa);
    Jugador enemigo(Coordinates(5,7), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    
    //act
	jugador.cambiarArma(0);
	int evento = bot.getEvent(&jugador, vec);
	
	//assert
	EXPECT_EQ (evento, Evento::MoverDerecha);
}

TEST(LuaTests, giraCorrectoADerechaMirandoAArriba) {
    //arrange
    Mapa mapa(10, 10);
    Bot bot(mapa);
    Jugador jugador(Coordinates(5,5), Coordinates(0, 1),  mapa);
    Jugador enemigo(Coordinates(7,5), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    
    //act
	jugador.cambiarArma(0);
	int evento = bot.getEvent(&jugador, vec);
	
	//assert
	EXPECT_EQ (evento, Evento::MoverDerecha);
}

TEST(LuaTests, giraCorrectoADerechaMirandoAAbajo) {
    //arrange
    Mapa mapa(10, 10);
    Bot bot(mapa);
    Jugador jugador(Coordinates(5,5), Coordinates(0, -1),  mapa);
    Jugador enemigo(Coordinates(3,5), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    
    //act
	jugador.cambiarArma(0);
	int evento = bot.getEvent(&jugador, vec);
	
	//assert
	EXPECT_EQ (evento, Evento::MoverDerecha);
}

TEST(LuaTests, giraCorrectoAIzquierdaMirandoADerecha) {
    //arrange
    Mapa mapa(10, 10);
    Bot bot(mapa);
    Jugador jugador(Coordinates(5,5), Coordinates(1, 0),  mapa);
    Jugador enemigo(Coordinates(5,7), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    
    //act
	jugador.cambiarArma(0);
	int evento = bot.getEvent(&jugador, vec);
	
	//assert
	EXPECT_EQ (evento, Evento::MoverIzquierda);
}

TEST(LuaTests, giraCorrectoAIzquierdaMirandoAIzquierda) {
    //arrange
    Mapa mapa(10, 10);
    Bot bot(mapa);
    Jugador jugador(Coordinates(5,5), Coordinates(-1, 0),  mapa);
    Jugador enemigo(Coordinates(5,3), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    
    //act
	jugador.cambiarArma(0);
	int evento = bot.getEvent(&jugador, vec);
	
	//assert
	EXPECT_EQ (evento, Evento::MoverIzquierda);
}

TEST(LuaTests, giraCorrectoAIzquierdaMirandoAArriba) {
    //arrange
    Mapa mapa(10, 10);
    Bot bot(mapa);
    Jugador jugador(Coordinates(5,5), Coordinates(0, 1),  mapa);
    Jugador enemigo(Coordinates(3,5), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    
    //act
	jugador.cambiarArma(0);
	int evento = bot.getEvent(&jugador, vec);
	
	//assert
	EXPECT_EQ (evento, Evento::MoverIzquierda);
}

TEST(LuaTests, giraCorrectoAIzquierdaMirandoAAbajo) {
    //arrange
    Mapa mapa(10, 10);
    Bot bot(mapa);
    Jugador jugador(Coordinates(5,5), Coordinates(0, -1),  mapa);
    Jugador enemigo(Coordinates(7,5), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    
    //act
	jugador.cambiarArma(0);
	int evento = bot.getEvent(&jugador, vec);
	
	//assert
	EXPECT_EQ (evento, Evento::MoverIzquierda);
}

TEST(LuaTests, persigueAlEnemigoMasCercano) {
    //arrange
    Mapa mapa(10, 10);
    Bot bot(mapa);
    Jugador jugador(Coordinates(5,5), Coordinates(1, 0),  mapa);
    Jugador enemigo1(Coordinates(5,9), Coordinates(1, 0),  mapa); // Distancia 4
    Jugador enemigo2(Coordinates(5,2), Coordinates(1, 0),  mapa); // Distancia 3
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo1);
    vec.push_back(&enemigo2);
    
    //act
	jugador.cambiarArma(0);
	int evento = bot.getEvent(&jugador, vec);
	
	//assert
	EXPECT_EQ (evento, Evento::MoverDerecha); // Distancia 3
}

TEST(LuaTests, persigueAlMismoEnemigoVariosCiclos) {
    Mapa mapa(10, 10);
    Bot bot(mapa);
    Jugador jugador(Coordinates(5,5), Coordinates(1, 0),  mapa);
    Jugador enemigo1(Coordinates(5,9), Coordinates(1, 0),  mapa); // Distancia 4
    Jugador enemigo2(Coordinates(5,2), Coordinates(1, 0),  mapa); // Distancia 3
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo1);
    
	jugador.cambiarArma(0);
	int evento = bot.getEvent(&jugador, vec);
	EXPECT_EQ (evento, Evento::MoverIzquierda); // Enemigo 1
	
    vec.push_back(&enemigo2);
    EXPECT_EQ (bot.getEvent(&jugador, vec), Evento::MoverIzquierda);// Enemigo 1
    EXPECT_EQ (bot.getEvent(&jugador, vec), Evento::MoverIzquierda);// Enemigo 1
    EXPECT_EQ (bot.getEvent(&jugador, vec), Evento::MoverIzquierda);// Enemigo 1
    EXPECT_EQ (bot.getEvent(&jugador, vec), Evento::MoverIzquierda);// Enemigo 1
}
*/
