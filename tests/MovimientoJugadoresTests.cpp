#include "gtest/gtest.h"
#include "Jugador.h"
#include "Mapa.h"
#include "Direccion.h"
#include "Angulo.h"
#include "Posicion.h"
#include "Posicionable.h"
//-------------------- Hacia adelante ------------------------------------
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeDerecha) {
    //arrange
    Mapa mapa(20,20);
    bool lugar_vacio = false;
    //Mirando hacia la derecha
    Angulo angulo(0.0);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());

    Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
    if (vacio == NULL)
        lugar_vacio = true;
    //assert
    EXPECT_EQ (lugar_vacio, true);
    EXPECT_EQ (posicionIni.getPosX() + 1, resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY(), resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeArriba) {
    //arrange
    Mapa mapa(20,20);
    bool lugar_vacio = false;
    //Mirando hacia la arriba
    Angulo angulo(90.0);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());

    Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
    if (vacio == NULL)
        lugar_vacio = true;
    //assert
    EXPECT_EQ (lugar_vacio, true);
    EXPECT_EQ (posicionIni.getPosX(), resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY() + 1, resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeIzquierda) {
    //arrange
    Mapa mapa(20,20);
    bool lugar_vacio = false;
    //Mirando hacia la izquierda
    //Poner 00 despues de la coma
    Angulo angulo(180.00);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());

    Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
    if (vacio == NULL)
        lugar_vacio = true;
    //assert
    EXPECT_EQ (lugar_vacio, true);
    EXPECT_EQ (posicionIni.getPosX() - 1, resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY(), resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeAbajo) {
    //arrange
    Mapa mapa(20,20);
    bool lugar_vacio = false;
    //Mirando hacia abajo
    //Poner 00 despues de la coma
    Angulo angulo(-90.00);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());

    Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
    if (vacio == NULL)
        lugar_vacio = true;
    //assert
    EXPECT_EQ (lugar_vacio, true);
    EXPECT_EQ (posicionIni.getPosX(), resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY() - 1, resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeDerechaArriba) {
    //arrange
    Mapa mapa(20,20);
    bool lugar_vacio = false;
    //Mirando hacia arriba y a la derecha
    //Poner 00 despues de la coma
    Angulo angulo(45.00);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());

    Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
    if (vacio == NULL)
        lugar_vacio = true;
    //assert
    EXPECT_EQ (lugar_vacio, true);
    EXPECT_EQ (posicionIni.getPosX() + 1, resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY() + 1, resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeDerechaAbajo) {
    //arrange
    Mapa mapa(20,20);
    bool lugar_vacio = false;
    //Mirando hacia abajo y hacia la derecha
    //Poner 00 despues de la coma
    Angulo angulo(-45.00);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());

    Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
    if (vacio == NULL)
        lugar_vacio = true;
    //assert
    EXPECT_EQ (lugar_vacio, true);
    EXPECT_EQ (posicionIni.getPosX() + 1, resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY() - 1, resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeIzquierdaArriba) {
    //arrange
    Mapa mapa(20,20);
    bool lugar_vacio = false;
    //Mirando hacia arriba y hacia la izquierda
    //Poner 00 despues de la coma
    Angulo angulo(135.00);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());

    Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
    if (vacio == NULL)
        lugar_vacio = true;
    //assert
    EXPECT_EQ (lugar_vacio, true);
    EXPECT_EQ (posicionIni.getPosX() - 1, resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY() + 1, resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeIzquierdaAbajo) {
    //arrange
    Mapa mapa(20,20);
    bool lugar_vacio = false;
    //Mirando hacia abajo y hacia la izquierda
    //Poner 00 despues de la coma
    Angulo angulo(-135.00);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());

    Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
    if (vacio == NULL)
        lugar_vacio = true;
    //assert
    EXPECT_EQ (lugar_vacio, true);
    EXPECT_EQ (posicionIni.getPosX() - 1, resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY() - 1, resultado->getPosicion().getPosY());
}

// ---------------------------------------------------------
// ---------------------- Hacia atras ----------------------
// ---------------------------------------------------------

TEST(MovimientoJugadoresTests, atrasExitosoDesdeDerecha) {
    //arrange
    Mapa mapa(20,20);
    //Mirando hacia la derecha
    Angulo angulo(0.0);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAtras dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX() - 1, resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY(), resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, atrasExitosoDesdeArriba) {
    //arrange
    Mapa mapa(20,20);
    //Mirando hacia la arriba
    Angulo angulo(90.0);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAtras dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX(), resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY() - 1, resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, atrasExitosoDesdeIzquierda) {
    //arrange
    Mapa mapa(20,20);
    //Mirando hacia la izquierda
    //Poner 00 despues de la coma
    Angulo angulo(180.00);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAtras dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX() + 1, resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY(), resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, atrasExitosoDesdeAbajo) {
    //arrange
    Mapa mapa(20,20);
    //Mirando hacia abajo
    //Poner 00 despues de la coma
    Angulo angulo(-90.00);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAtras dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX(), resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY() + 1, resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, atrasExitosoDesdeDerechaArriba) {
    //arrange
    Mapa mapa(20,20);
    //Mirando hacia arriba y a la derecha
    //Poner 00 despues de la coma
    Angulo angulo(45.00);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAtras dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX() - 1, resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY() - 1, resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, atrasExitosoDesdeDerechaAbajo) {
    //arrange
    Mapa mapa(20,20);
    //Mirando hacia abajo y hacia la derecha
    //Poner 00 despues de la coma
    Angulo angulo(-45.00);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAtras dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX() - 1, resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY() + 1, resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, atrasExitosoDesdeIzquierdaArriba) {
    //arrange
    Mapa mapa(20,20);
    //Mirando hacia arriba y hacia la izquierda
    //Poner 00 despues de la coma
    Angulo angulo(135.00);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAtras dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX() + 1, resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY() - 1, resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, atrasExitosoDesdeIzquierdaAbajo) {
    //arrange
    Mapa mapa(20,20);
    //Mirando hacia abajo y hacia la izquierda
    //Poner 00 despues de la coma
    Angulo angulo(-135.00);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAtras dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX() + 1, resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY() + 1, resultado->getPosicion().getPosY());
}

// ---------------------------------------------------------
// ---------------------- Fuera del mapa -------------------
// ---------------------------------------------------------

TEST(MovimientoJugadoresTests, adelanteFallaIrDerechaFuera) {
    //arrange
    Mapa mapa(20,20);
    //Mirando hacia derecha
    //Poner 00 despues de la coma
    Angulo angulo(0.00);
    Posicion posicionIni(20,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    try {
        jugador.mover(&dir);
    } catch (...){
    }
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX(), resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY(), resultado->getPosicion().getPosY());
}

TEST(MovimientoJugadoresTests, adelanteFallaIrArribaFuera) {
    //arrange
    Mapa mapa(20,20);
    //Mirando hacia arriba
    //Poner 00 despues de la coma
    Angulo angulo(90.00);
    Posicion posicionIni(11,20, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    try {
        jugador.mover(&dir);
    } catch (...){
    }
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX(), resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY(), resultado->getPosicion().getPosY());
}

TEST(MovimientoJugadoresTests, adelanteFallaIrIzquierdaFuera) {
    //arrange
    Mapa mapa(20,20);
    //Mirando hacia izquierda
    //Poner 00 despues de la coma
    Angulo angulo(180.00);
    Posicion posicionIni(0,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    try {
        jugador.mover(&dir);
    } catch (...){
    }
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX(), resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY(), resultado->getPosicion().getPosY());
}

TEST(MovimientoJugadoresTests, adelanteFallaIrAbajoFuera) {
    //arrange
    Mapa mapa(20,20);
    //Mirando hacia abajo
    //Poner 00 despues de la coma
    Angulo angulo(-90.00);
    Posicion posicionIni(11,0, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    try {
        jugador.mover(&dir);
    } catch (...){
    }
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX(), resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY(), resultado->getPosicion().getPosY());
}

// ---------------------------------------------------------
// ------------- Colisiones entre posicionables ------------
// ---------------------------------------------------------

TEST(MovimientoJugadoresTests, adelanteFallaIrDerechaEncimaDeOtroJugador) {
    //arrange
    Mapa mapa(20,20);
    //Mirando hacia derecha
    //Poner 00 despues de la coma
    Angulo angulo(0.00);
    Posicion posicionIni2(12,0, angulo);
    Jugador jugador2(posicionIni2, mapa);
    Posicion posicionIni(11,0, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    try {
        jugador.mover(&dir);
    } catch (...){
    }
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX(), resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY(), resultado->getPosicion().getPosY());
}
