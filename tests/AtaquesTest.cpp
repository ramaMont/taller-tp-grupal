#include "gtest/gtest.h"
#include "Mapa.h"
#include "Jugador.h"
#include "Item.h"
#include "Posicionable.h"
#include "Objeto.h"
#include <vector>

#define N_CUCHILLO 0
#define N_PISTOLA 1
#define N_AMETRALLADORA 2
#define N_CANION 3
#define N_LANZACOHETES 4


TEST(AtaquesTests, cuchilloAtacaDistancia1Adelante) {
    //arrange
    Mapa mapa(20,20);
    Jugador jugador(Coordinates(5, 5), Coordinates(1, 0),  mapa);
    Jugador enemigo(Coordinates(6, 5), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    int vida_inicial = jugador.getVida();
    
    //act
	jugador.cambiarArma(N_CUCHILLO);
	jugador.disparar(vec);
	int vida = enemigo.getVida();
	
    //assert
    EXPECT_TRUE (vida < vida_inicial);
}

TEST(AtaquesTests, cuchilloAtacaDistancia1Izquierda) {
    //arrange
    Mapa mapa(20,20);
    Jugador jugador(Coordinates(5, 5), Coordinates(1, 0),  mapa);
    Jugador enemigo(Coordinates(6, 6), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    int vida_inicial = jugador.getVida();
    
    //act
	jugador.cambiarArma(N_CUCHILLO);
	jugador.disparar(vec);
	int vida = enemigo.getVida();
	
    //assert
    EXPECT_TRUE (vida < vida_inicial);
}

TEST(AtaquesTests, cuchilloAtacaDistancia1Derecha) {
    //arrange
    Mapa mapa(20,20);
    Jugador jugador(Coordinates(5, 5), Coordinates(1, 0),  mapa);
    Jugador enemigo(Coordinates(6, 4), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    int vida_inicial = jugador.getVida();
    
    //act
	jugador.cambiarArma(N_CUCHILLO);
	jugador.disparar(vec);
	int vida = enemigo.getVida();
	
    //assert
    EXPECT_TRUE (vida < vida_inicial);
}

TEST(AtaquesTests, cuchilloNoAtacaDistanciaMasDe2) {
    //arrange
    Mapa mapa(20,20);
    Jugador jugador(Coordinates(5, 5), Coordinates(1, 0),  mapa);
    Jugador enemigo(Coordinates(7, 5), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    int vida_inicial = jugador.getVida();
    
    //act
	jugador.cambiarArma(N_CUCHILLO);
	jugador.disparar(vec);
	int vida = enemigo.getVida();
	
    //assert
    EXPECT_TRUE (vida == vida_inicial);
}

TEST(AtaquesTests, cuchilloNoAtacaAtras) {
    //arrange
    Mapa mapa(20,20);
    Jugador jugador(Coordinates(5, 5), Coordinates(1, 0),  mapa);
    Jugador enemigo(Coordinates(5, 4), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    int vida_inicial = jugador.getVida();
    
    //act
	jugador.cambiarArma(N_CUCHILLO);
	jugador.disparar(vec);
	int vida = enemigo.getVida();
	
    //assert
    EXPECT_TRUE (vida == vida_inicial);
}

TEST(AtaquesTests, pistolaAtacaEnemigoEnfrente) {
    //arrange
    Mapa mapa(20,20);
    Jugador jugador(Coordinates(5, 5), Coordinates(1, 0),  mapa);
    Jugador enemigo(Coordinates(10,5), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    int vida_inicial = jugador.getVida();
    
    //act
	jugador.cambiarArma(N_PISTOLA);
	jugador.disparar(vec);
	int vida = enemigo.getVida();
	
    //assert
    EXPECT_TRUE (vida < vida_inicial);
}

TEST(AtaquesTests, pistolaAtacaEnemigoEnSuRangoDeVision) {
    //arrange
    Mapa mapa(20,20);
    Jugador jugador(Coordinates(5, 5), Coordinates(1, 0),  mapa);
    Jugador enemigo(Coordinates(10,6), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    int vida_inicial = jugador.getVida();
    
    //act
	jugador.cambiarArma(N_PISTOLA);
	jugador.disparar(vec);
	int vida = enemigo.getVida();
	
    //assert
    EXPECT_TRUE (vida < vida_inicial);
}

TEST(AtaquesTests, pistolaNoAtacaEmemigoAlCostado) {
    //arrange
    Mapa mapa(20,20);
    Jugador jugador(Coordinates(5, 5), Coordinates(1, 0),  mapa);
    Jugador enemigo(Coordinates(5, 8), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    int vida_inicial = jugador.getVida();
    
    //act
	jugador.cambiarArma(N_PISTOLA);
	jugador.disparar(vec);
	int vida = enemigo.getVida();
	
    //assert
    EXPECT_TRUE (vida == vida_inicial);
}

TEST(AtaquesTests, pistolaNoAtacaEmemigoAtras) {
    //arrange
    Mapa mapa(20,20);
    Jugador jugador(Coordinates(5, 5), Coordinates(1, 0),  mapa);
    Jugador enemigo(Coordinates(3, 5), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    int vida_inicial = jugador.getVida();
    
    //act
	jugador.cambiarArma(N_PISTOLA);
	jugador.disparar(vec);
	int vida = enemigo.getVida();
	
    //assert
    EXPECT_TRUE (vida == vida_inicial);
}

TEST(AtaquesTests, pistolaNoAtacaSiHayObjetoEnElMedio) {
    //arrange
    Mapa mapa(20,20);
    Jugador jugador(Coordinates(5, 5), Coordinates(1, 0),  mapa);
    Jugador enemigo(Coordinates(10,5), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    int vida_inicial = jugador.getVida();
    Coordinates posicion(8, 5);
    Objeto pared(posicion);
    
    //act
    mapa.agregarPosicionable(&pared, posicion);
	jugador.cambiarArma(N_PISTOLA);
	jugador.disparar(vec);
	int vida = enemigo.getVida();
	
    //assert
    EXPECT_TRUE (vida == vida_inicial);
}

TEST(AtaquesTests, pistolaAtacaAlEnemigoEnfrentadoEnElMenorAngulo) {
    //arrange
    Mapa mapa(20,20);
    Jugador jugador(Coordinates(5, 5), Coordinates(1, 0),  mapa);
    Jugador enemigo1(Coordinates(15,6), Coordinates(1, 0),  mapa);
    Jugador enemigo2(Coordinates(15,7), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo1);
    vec.push_back(&enemigo2);
    int vida_inicial = jugador.getVida();
    
    //act
	jugador.cambiarArma(N_PISTOLA);
	jugador.disparar(vec);
	int vida_enemigo1 = enemigo1.getVida();
	int vida_enemigo2 = enemigo2.getVida();
	
    //assert
    EXPECT_TRUE (vida_enemigo1 < vida_inicial);
    EXPECT_TRUE (vida_enemigo2 == vida_inicial);
}

TEST(AtaquesTests, ametralladoraAtacaEnemigoEnfrente) {
    //arrange
    Mapa mapa(20,20);
    Jugador jugador(Coordinates(5, 5), Coordinates(1, 0),  mapa);
    Jugador enemigo(Coordinates(10,5), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    int vida_inicial = jugador.getVida();
    Coordinates posicion(5,5);
    Ametralladora ametralladora(posicion);
    
    //act
    jugador.agregarArma(&ametralladora);
	jugador.cambiarArma(N_AMETRALLADORA);
	jugador.disparar(vec);
	int vida = enemigo.getVida();
	
    //assert
    EXPECT_TRUE (vida < vida_inicial);
}

TEST(AtaquesTests, ametralladoraNoAtacaEnemigoAtras) {
    //arrange
    Mapa mapa(20,20);
    Jugador jugador(Coordinates(10,5), Coordinates(1, 0),  mapa);
    Jugador enemigo(Coordinates(5, 5), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    int vida_inicial = jugador.getVida();
    Coordinates posicion(5,5);
    Ametralladora ametralladora(posicion);
    
    //act
    jugador.agregarArma(&ametralladora);
	jugador.cambiarArma(N_AMETRALLADORA);
	jugador.disparar(vec);
	int vida = enemigo.getVida();
	
    //assert
    EXPECT_TRUE (vida == vida_inicial);
}

TEST(AtaquesTests, canionAtacaEnemigoEnfrente) {
    //arrange
    Mapa mapa(20,20);
    Jugador jugador(Coordinates(5, 5), Coordinates(1, 0),  mapa);
    Jugador enemigo(Coordinates(10,5), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    int vida_inicial = jugador.getVida();
    Coordinates posicion(5,5);
    CanionDeCadena canion(posicion);
    
    //act
    jugador.agregarArma(&canion);
	jugador.cambiarArma(N_CANION);
	jugador.disparar(vec);
	int vida = enemigo.getVida();
	
    //assert
    EXPECT_TRUE (vida < vida_inicial);
}

TEST(AtaquesTests, canionNoAtacaEnemigoAtras) {
    //arrange
    Mapa mapa(20,20);
    Jugador jugador(Coordinates(10,5), Coordinates(1, 0),  mapa);
    Jugador enemigo(Coordinates(5, 5), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo);
    int vida_inicial = jugador.getVida();
    Coordinates posicion(5,5);
    CanionDeCadena canion(posicion);
    
    //act
    jugador.agregarArma(&canion);
	jugador.cambiarArma(N_CANION);
	jugador.disparar(vec);
	int vida = enemigo.getVida();
	
    //assert
    EXPECT_TRUE (vida == vida_inicial);
}

TEST(AtaquesTests, lanzacohetesAtacaTodosLosEnemigosCercanos) {
    //arrange
    Mapa mapa(20,20);
    Jugador jugador(Coordinates(7, 10), Coordinates(1, 0),  mapa);
    Jugador enemigo1(Coordinates(10,10), Coordinates(1, 0),  mapa);
    Jugador enemigo2(Coordinates(10,12), Coordinates(1, 0),  mapa);
    Jugador enemigo3(Coordinates(10, 8), Coordinates(1, 0),  mapa);
    Jugador enemigo4(Coordinates(12,10), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo1);
    vec.push_back(&enemigo2);
    vec.push_back(&enemigo3);
    vec.push_back(&enemigo4);
    int vida_inicial = jugador.getVida();
    Coordinates posicion(7,10);
    Lanzacohetes lanzacohetes(posicion);
    
    //act
    jugador.agregarArma(&lanzacohetes);
	jugador.cambiarArma(N_LANZACOHETES);
	jugador.disparar(vec);
	int vida_jugador = jugador.getVida();
	int vida_enemigo1 = enemigo1.getVida();
	int vida_enemigo2 = enemigo2.getVida();
	int vida_enemigo3 = enemigo3.getVida();
	int vida_enemigo4 = enemigo4.getVida();
	
    //assert
    EXPECT_TRUE (vida_jugador < vida_inicial);
    EXPECT_TRUE (vida_enemigo1 < vida_inicial);
    EXPECT_TRUE (vida_enemigo2 < vida_inicial);
    EXPECT_TRUE (vida_enemigo3 < vida_inicial);
    EXPECT_TRUE (vida_enemigo4 < vida_inicial);
}

TEST(AtaquesTests, lanzacohetesNoAtacaEnemigosLejanos) {
    //arrange
    Mapa mapa(40,40);
    Jugador jugador(Coordinates(7, 10), Coordinates(1, 0),  mapa);
    Jugador enemigo1(Coordinates(10,10), Coordinates(1, 0),  mapa);
    Jugador enemigo2(Coordinates(35,35), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo1);
    vec.push_back(&enemigo2);
    int vida_inicial = jugador.getVida();
    Coordinates posicion(7,10);
    Lanzacohetes lanzacohetes(posicion);
    
    //act
    jugador.agregarArma(&lanzacohetes);
	jugador.cambiarArma(N_LANZACOHETES);
	jugador.disparar(vec);
	int vida_jugador = jugador.getVida();
	int vida_enemigo1 = enemigo1.getVida();
	int vida_enemigo2 = enemigo2.getVida();
	
    //assert
    EXPECT_TRUE (vida_jugador < vida_inicial);
    EXPECT_TRUE (vida_enemigo1 < vida_inicial);
    EXPECT_TRUE (vida_enemigo2 == vida_inicial);
}

TEST(AtaquesTests, lanzacohetesNoAtacaSiUnObjetoSeInterpone) {
    //arrange
    Mapa mapa(40,40);
    Jugador jugador(Coordinates(7, 10), Coordinates(1, 0),  mapa);
    Jugador enemigo1(Coordinates(10,10), Coordinates(1, 0),  mapa);
    Jugador enemigo2(Coordinates(12,10), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo1);
    vec.push_back(&enemigo2);
    int vida_inicial = jugador.getVida();
    Coordinates posicion(7,10);
    Lanzacohetes lanzacohetes(posicion);
    Objeto pared(Coordinates(11,10));
    mapa.agregarPosicionable(&pared, Coordinates(11,10));
    
    //act
    jugador.agregarArma(&lanzacohetes);
	jugador.cambiarArma(N_LANZACOHETES);
	jugador.disparar(vec);
	int vida_jugador = jugador.getVida();
	int vida_enemigo1 = enemigo1.getVida();
	int vida_enemigo2 = enemigo2.getVida();
	
    //assert
    EXPECT_TRUE (vida_jugador < vida_inicial);
    EXPECT_TRUE (vida_enemigo1 < vida_inicial);
    EXPECT_TRUE (vida_enemigo2 == vida_inicial);
}

TEST(AtaquesTests, lanzacohetesMasDanioMasCerca) {
    //arrange
    Mapa mapa(20,20);
    Jugador jugador(Coordinates(7, 10), Coordinates(1, 0),  mapa);
    Jugador enemigo1(Coordinates(10,10), Coordinates(1, 0),  mapa);
    Jugador enemigo2(Coordinates(10, 8), Coordinates(1, 0),  mapa);
    Jugador enemigo3(Coordinates(10, 15), Coordinates(1, 0),  mapa);
    Jugador enemigo4(Coordinates(18,10), Coordinates(1, 0),  mapa);
    std::vector<Jugador*> vec;
    vec.push_back(&jugador);
    vec.push_back(&enemigo1);
    vec.push_back(&enemigo2);
    vec.push_back(&enemigo3);
    vec.push_back(&enemigo4);
    int vida_inicial = jugador.getVida();
    Coordinates posicion(7,10);
    Lanzacohetes lanzacohetes(posicion);
    
    //act
    jugador.agregarArma(&lanzacohetes);
	jugador.cambiarArma(N_LANZACOHETES);
	jugador.disparar(vec);
	int vida_enemigo1 = enemigo1.getVida(); // Distancia 0
	int vida_enemigo2 = enemigo2.getVida(); // Distancia 2
	int vida_enemigo3 = enemigo3.getVida(); // Distancia 5
	int vida_enemigo4 = enemigo4.getVida(); // Distancia 8
	
    //assert
    EXPECT_TRUE (vida_enemigo1 < vida_enemigo2);
    EXPECT_TRUE (vida_enemigo2 < vida_enemigo3);
    EXPECT_TRUE (vida_enemigo3 < vida_enemigo4);
    EXPECT_TRUE (vida_enemigo4 < vida_inicial);
}

