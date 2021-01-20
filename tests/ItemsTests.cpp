#include "gtest/gtest.h"
#include "Mapa.h"
#include "Player.h"
#include "Item.h"
#include "Posicionable.h"
#include "Event.h"
#include <iostream>

TEST(ItemsTests, comidaRecupera10puntosDeVida) {
    //arrange
    Mapa mapa(20,20);
    BlockingQueue<Protocol> bq;
    Player* jugador = new Player(Coordinates(5,5), Coordinates(1,0), mapa, bq);
    Comida* comida = new Comida(Coordinates(6,5));
    mapa.agregarItem(comida, Coordinates(6,5));
    int vida_maxima = jugador->getVida();
    
    //act
    int danio = 10; 
    jugador->recibirDanio(danio); // Para bajar su vida
    
    DirAdelante dirAdelante;
    while (jugador->get_coordinates() != Coordinates(6,5)){
        jugador->mover(&dirAdelante);
    }
    int vida = jugador->getVida();
 
    //assert
    EXPECT_EQ (vida_maxima, vida);
}

/*
TEST(ItemsTests, kitMedicoRecupera20puntosDeVida) {
    //arrange
    Mapa mapa(20,20);
    Coordinates posicion(11, 15);
    Coordinates direccion(1, 0);
    Jugador jugador(posicion, direccion,  mapa);
    KitMedico kit(posicion);
    int vida_maxima = jugador.getVida();
    
    //act
	int danio = 25; 
    jugador.recibirDanio(danio); // Para bajar su vida
    int vida = jugador.getVida();
    //assert
    EXPECT_EQ (vida, vida_maxima-danio);
    
    //act
    jugador.usar(&kit); 
    int vida_nueva = jugador.getVida();
    //assert
    EXPECT_EQ (vida_nueva, vida + 20);
}

TEST(ItemsTests, sangreRecupera1PuntoDeVidaSiEstaBaja) {
    //arrange
    Mapa mapa(20,20);
    Coordinates posicion(11, 15);
    Coordinates direccion(1, 0);
    Jugador jugador(posicion, direccion,  mapa);
    Sangre sangre(posicion);
    
    //act
    int vida = jugador.getVida();
	int danio = 1; 
	while (vida > 10){
		jugador.recibirDanio(danio); // Para bajar su vida
		vida = jugador.getVida();
	}
    //assert
    EXPECT_EQ (vida, 10);
    
    //act
    bool usa_sangre = jugador.usar(&sangre); 
    vida = jugador.getVida();
    //assert
    EXPECT_EQ (vida, 11);
    EXPECT_EQ (usa_sangre, true);
}

TEST(ItemsTests, noUsaSangreSiTieneMuchaVida) {
    //arrange
    Mapa mapa(20,20);
    Coordinates posicion(11, 15);
    Coordinates direccion(1, 0);
    Jugador jugador(posicion, direccion,  mapa);
    Sangre sangre(posicion);
    
    //act
    int vida = jugador.getVida();
	int danio = 1; 
	while (vida > 20){
		jugador.recibirDanio(danio); // Para bajar su vida
		vida = jugador.getVida();
	}
	bool usa_sangre = jugador.usar(&sangre); 
    //assert
    EXPECT_EQ (vida, 20);
    EXPECT_EQ (usa_sangre, false);
    
    //act
	while (vida > 12){
		jugador.recibirDanio(danio); // Para bajar su vida
		vida = jugador.getVida();
	}
	usa_sangre = jugador.usar(&sangre); 
    //assert
    EXPECT_EQ (vida, 12);
    EXPECT_EQ (usa_sangre, false);
}

TEST(ItemsTests, noPuedeRecuperarMasDelMaximoDeVida) {
    //arrange
    Mapa mapa(20,20);
    Coordinates posicion(11, 15);
    Coordinates direccion(1, 0);
    Jugador jugador(posicion, direccion,  mapa);
    KitMedico kit(posicion);
    int vida_maxima = jugador.getVida();
    
    //act
	int danio = 15; 
    jugador.recibirDanio(danio); // Para bajar su vida
    bool usa_kit = jugador.usar(&kit);
    int vida = jugador.getVida();
    //assert
    EXPECT_EQ (vida, vida_maxima);
    EXPECT_EQ (usa_kit, true);
}

TEST(ItemsTests, agarrarBalasAumentaEn5laCantidad) {
    //arrange
    Mapa mapa(20,20);
    Coordinates posicion(11, 15);
    Coordinates direccion(1, 0);
    Jugador jugador(posicion, direccion,  mapa);
    Balas balas(posicion);
    int balas_iniciales = jugador.getBalas();
    
    //act
    bool usa = jugador.usar(&balas);
    int balas_actuales = jugador.getBalas();
    //assert
    EXPECT_EQ (usa, true);
    EXPECT_EQ (balas_iniciales + 5, balas_actuales);
}

TEST(ItemsTests, tesorosAumentanLaPuntuacionCorrectamente) {
    //arrange
    Mapa mapa(20,20);
    Coordinates posicion(11, 15);
    Coordinates direccion(1, 0);
    Jugador jugador(posicion, direccion,  mapa);
    size_t puntaje = jugador.getPuntuacion();
    Cruz cruz(posicion);
    Copa copa(posicion);
    Cofre cofre(posicion);
    Corona corona(posicion);
    size_t p_cruz = 10;
    size_t p_copa = 50;
    size_t p_cofre = 100;
    size_t p_corona = 200;
    
    jugador.usar(&cruz);
    size_t nuevo_puntaje = jugador.getPuntuacion();
    EXPECT_EQ (puntaje + p_cruz, nuevo_puntaje);
    
    jugador.usar(&copa);
    nuevo_puntaje = jugador.getPuntuacion();
    EXPECT_EQ (puntaje + p_cruz + p_copa, nuevo_puntaje);
   
    jugador.usar(&cofre);
    nuevo_puntaje = jugador.getPuntuacion();
    EXPECT_EQ (puntaje + p_cruz + p_copa + p_cofre, nuevo_puntaje);
   
    jugador.usar(&corona);
    nuevo_puntaje = jugador.getPuntuacion();
    EXPECT_EQ (puntaje + p_cruz + p_copa + p_cofre + p_corona, nuevo_puntaje);
}
*/
