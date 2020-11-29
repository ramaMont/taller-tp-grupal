#include "gtest/gtest.h"
#include "Jugador.h"
#include "Mapa.h"
#include "Posicion.h"
#include "Posicionable.h"

TEST(ItemsTests, comidaRecupera10puntosDeVida) {
    //arrange
    Mapa mapa(20,20);
    Posicion posicion(11,15, Angulo(0.0));
    Jugador jugador(posicion, mapa);
    Comida comida(posicion);
    int vida_maxima = jugador.getVida();
    
    //act
	int danio = 20; 
    jugador.recibirDanio(danio); // Para bajar su vida
    int vida = jugador.getVida();
    //assert
    EXPECT_EQ (vida, vida_maxima-danio);
    
    //act
    jugador.usar(&comida); 
    int vida_nueva = jugador.getVida();
    //assert
    EXPECT_EQ (vida_nueva, vida + 10);
}

TEST(ItemsTests, kitMedicoRecupera20puntosDeVida) {
    //arrange
    Mapa mapa(20,20);
    Posicion posicion(11,15, Angulo(0.0));
    Jugador jugador(posicion, mapa);
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
    Posicion posicion(11,15, Angulo(0.0));
    Jugador jugador(posicion, mapa);
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
    Posicion posicion(11,15, Angulo(0.0));
    Jugador jugador(posicion, mapa);
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
    Posicion posicion(11,15, Angulo(0.0));
    Jugador jugador(posicion, mapa);
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
    Posicion posicion(11,15, Angulo(0.0));
    Jugador jugador(posicion, mapa);
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
    Posicion posicion(11,15, Angulo(0.0));
    Jugador jugador(posicion, mapa);
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
