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
    Mapa mapa;
    //Mirando hacia la derecha
    Angulo angulo(0.0);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX() + 1, resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY(), resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeArriba) {
    //arrange
    Mapa mapa;
    //Mirando hacia la arriba
    Angulo angulo(90.0);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX(), resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY() + 1, resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeIzquierda) {
    //arrange
    Mapa mapa;
    //Mirando hacia la izquierda
    //Poner 00 despues de la coma
    Angulo angulo(180.00);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX() - 1, resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY(), resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeAbajo) {
    //arrange
    Mapa mapa;
    //Mirando hacia abajo
    //Poner 00 despues de la coma
    Angulo angulo(-90.00);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX(), resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY() - 1, resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeDerechaArriba) {
    //arrange
    Mapa mapa;
    //Mirando hacia arriba y a la derecha
    //Poner 00 despues de la coma
    Angulo angulo(45.00);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX() + 1, resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY() + 1, resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeDerechaAbajo) {
    //arrange
    Mapa mapa;
    //Mirando hacia abajo y hacia la derecha
    //Poner 00 despues de la coma
    Angulo angulo(-45.00);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX() + 1, resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY() - 1, resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeIzquierdaArriba) {
    //arrange
    Mapa mapa;
    //Mirando hacia arriba y hacia la izquierda
    //Poner 00 despues de la coma
    Angulo angulo(135.00);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX() - 1, resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY() + 1, resultado->getPosicion().getPosY());
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeIzquierdaAbajo) {
    //arrange
    Mapa mapa;
    //Mirando hacia abajo y hacia la izquierda
    //Poner 00 despues de la coma
    Angulo angulo(-135.00);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ (posicionIni.getPosX() - 1, resultado->getPosicion().getPosX());
    EXPECT_EQ (posicionIni.getPosY() - 1, resultado->getPosicion().getPosY());
}

// ---------------------------------------------------------
// ---------------------- Hacia atras ----------------------
// ---------------------------------------------------------

TEST(MovimientoJugadoresTests, atrasExitosoDesdeDerecha) {
    //arrange
    Mapa mapa;
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
    Mapa mapa;
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
    Mapa mapa;
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
    Mapa mapa;
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
    Mapa mapa;
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
    Mapa mapa;
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
    Mapa mapa;
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
    Mapa mapa;
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