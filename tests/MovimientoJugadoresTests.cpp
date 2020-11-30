#include "gtest/gtest.h"
#include <Jugador.h>
#include <Mapa.h>
#include <Direccion.h>
#include <coordinates.h>
#include <Posicionable.h>

#include <cmath>

static float inc = 0.05;
static const float step_size = 0.1;
//-------------------- Hacia adelante ------------------------------------
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeDerecha) {
    //arrange
    Mapa mapa(20,20);
    float i;
    bool lugar_vacio = false;
    //Mirando hacia la derecha
    Coordinates angulo(1,0);
    Coordinates posicionIni(11, 15);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAdelante dir;
    //act
    for (i = 0.0; i < 1.0; i+=step_size)
        jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());

    Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
    if (vacio == nullptr)
        lugar_vacio = true;
    //assert
    EXPECT_EQ (lugar_vacio, true);
    EXPECT_EQ ((int) (int) posicionIni.x + i, (int) (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) (int) posicionIni.y, (int) (int) resultado->getPosicion().y);
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeArriba) {
    //arrange
    Mapa mapa(20,20);
    float i;
    bool lugar_vacio = false;
    //Mirando hacia la arriba
    Coordinates angulo(0,1);
    Coordinates posicionIni(11, 15);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAdelante dir;
    for (i = 0.0; i < 1.0; i+=step_size)
        jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
    if (vacio == nullptr)
        lugar_vacio = true;
    //assert
    EXPECT_EQ (lugar_vacio, true);
    EXPECT_EQ ((int) posicionIni.x, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y + i, (int) resultado->getPosicion().y);
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeIzquierda) {
    //arrange
    Mapa mapa(20,20);
    float i;
    bool lugar_vacio = false;
    //Mirando hacia la izquierda
    //Poner 00 despues de la coma
    Coordinates angulo(-1,0);
    Coordinates posicionIni(11, 15);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAdelante dir;
    for (i = 0.0; i < 1.0; i+=step_size)
        jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
    if (vacio == nullptr)
        lugar_vacio = true;
    //assert
    EXPECT_EQ (lugar_vacio, true);
    EXPECT_EQ ((int) posicionIni.x - i, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y, (int) resultado->getPosicion().y);
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeAbajo) {
    //arrange
    Mapa mapa(20,20);
    float i;
    bool lugar_vacio = false;
    //Mirando hacia abajo
    //Poner 00 despues de la coma
    Coordinates angulo(0,-1);
    Coordinates posicionIni(11, 15);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAdelante dir;
    for (i = 0.0; i < 1.0; i+=step_size)
        jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
    if (vacio == nullptr)
        lugar_vacio = true;
    //assert
    EXPECT_EQ (lugar_vacio, true);
    EXPECT_EQ ((int) posicionIni.x, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y - i, (int) resultado->getPosicion().y);
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeDerechaArriba) {
    //arrange
    Mapa mapa(20,20);
    float i;
    bool lugar_vacio = false;
    //Mirando hacia arriba y a la derecha
    //Poner 00 despues de la coma
    Coordinates angulo(1,1);
    Coordinates posicionIni(11, 15);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAdelante dir;
    for (i = 0.0; i < 1.0; i+=step_size)
        jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
    if (vacio == nullptr)
        lugar_vacio = true;
    //assert
    EXPECT_EQ (lugar_vacio, true);
    EXPECT_EQ ((int) posicionIni.x + i, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y + i, (int) resultado->getPosicion().y);
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeDerechaAbajo) {
    //arrange
    Mapa mapa(20,20);
    float i;
    bool lugar_vacio = false;
    //Mirando hacia abajo y hacia la derecha
    //Poner 00 despues de la coma
    Coordinates angulo(1,-1);
    Coordinates posicionIni(11, 15);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAdelante dir;
    for (i = 0.0; i < 1.0; i+=step_size)
        jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
    if (vacio == nullptr)
        lugar_vacio = true;
    //assert
    EXPECT_EQ (lugar_vacio, true);
    EXPECT_EQ ((int) posicionIni.x + i, (int) std::round(resultado->getPosicion().x));
    EXPECT_EQ ((int) posicionIni.y - i, (int) std::round(resultado->getPosicion().y));
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeIzquierdaArriba) {
    //arrange
    Mapa mapa(20,20);
    float i;
    bool lugar_vacio = false;
    //Mirando hacia arriba y hacia la izquierda
    //Poner 00 despues de la coma
    Coordinates angulo(-1,1);
    Coordinates posicionIni(11, 15);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAdelante dir;
    for (i = 0.0; i < 1.0; i+=step_size)
        jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
    if (vacio == nullptr)
        lugar_vacio = true;
    //assert
    EXPECT_EQ (lugar_vacio, true);
    EXPECT_EQ ((int) posicionIni.x - i, (int) std::round(resultado->getPosicion().x));
    EXPECT_EQ ((int) posicionIni.y + i, (int) std::round(resultado->getPosicion().y));
}
TEST(MovimientoJugadoresTests, adelanteExitosoDesdeIzquierdaAbajo) {
    //arrange
    Mapa mapa(20,20);
    float i;
    bool lugar_vacio = false;
    //Mirando hacia abajo y hacia la izquierda
    //Poner 00 despues de la coma
    Coordinates angulo(-1,-1);
    Coordinates posicionIni(11, 15);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAdelante dir;
    for (i = 0.0; i < 1.0; i+=step_size)
        jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
    if (vacio == nullptr)
        lugar_vacio = true;
    //assert
    EXPECT_EQ (lugar_vacio, true);
    EXPECT_EQ ((int) posicionIni.x - i, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y - i, (int) resultado->getPosicion().y);
}

// ---------------------------------------------------------
// ---------------------- Hacia atras ----------------------
// ---------------------------------------------------------

TEST(MovimientoJugadoresTests, atrasExitosoDesdeDerecha) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia la derecha
    Coordinates angulo(1,0);
    Coordinates posicionIni(11, 15);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAtras dir;
    for (i = 0.0; i < 1.0; i+=step_size)
        jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x - i, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y, (int) resultado->getPosicion().y);
}
TEST(MovimientoJugadoresTests, atrasExitosoDesdeArriba) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia la arriba
    Coordinates angulo(0,1);
    Coordinates posicionIni(11, 15);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAtras dir;
    for (i = 0.0; i < 1.0; i+=step_size)
        jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y - i, (int) resultado->getPosicion().y);
}
TEST(MovimientoJugadoresTests, atrasExitosoDesdeIzquierda) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia la izquierda
    //Poner 00 despues de la coma
    Coordinates angulo(-1,0);
    Coordinates posicionIni(11, 15);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAtras dir;
    for (i = 0.0; i < 1.0; i+=step_size)
        jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x + i, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y, (int) resultado->getPosicion().y);
}
TEST(MovimientoJugadoresTests, atrasExitosoDesdeAbajo) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia abajo
    //Poner 00 despues de la coma
    Coordinates angulo(0,-1);
    Coordinates posicionIni(11, 15);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAtras dir;
    for (i = 0.0; i < 1.0; i+=step_size)
        jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y + i, (int) resultado->getPosicion().y);
}
TEST(MovimientoJugadoresTests, atrasExitosoDesdeDerechaArriba) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia arriba y a la derecha
    //Poner 00 despues de la coma
    Coordinates angulo(1,1);
    Coordinates posicionIni(11, 15);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAtras dir;
    for (i = 0.0; i < 1.0; i+=step_size)
        jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x - i, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y - i, (int) resultado->getPosicion().y);
}
TEST(MovimientoJugadoresTests, atrasExitosoDesdeDerechaAbajo) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia abajo y hacia la derecha
    //Poner 00 despues de la coma
    Coordinates angulo(1,-1);
    Coordinates posicionIni(11, 15);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAtras dir;
    for (i = 0.0; i < 1.0; i+=step_size)
        jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x - i, (int) std::round(resultado->getPosicion().x));
    EXPECT_EQ ((int) posicionIni.y + i, (int) std::round(resultado->getPosicion().y));
}
TEST(MovimientoJugadoresTests, atrasExitosoDesdeIzquierdaArriba) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia arriba y hacia la izquierda
    //Poner 00 despues de la coma
    Coordinates angulo(-1,1);
    Coordinates posicionIni(11, 15);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAtras dir;
    for (i = 0.0; i < 1.0; i+=step_size)
        jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x + i, (int) std::round(resultado->getPosicion().x));
    EXPECT_EQ ((int) posicionIni.y - i, (int) std::round(resultado->getPosicion().y));
}
TEST(MovimientoJugadoresTests, atrasExitosoDesdeIzquierdaAbajo) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia abajo y hacia la izquierda
    //Poner 00 despues de la coma
    Coordinates angulo(-1,-1);
    Coordinates posicionIni(11, 15);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAtras dir;
    for (i = 0.0; i < 1.0; i+=step_size)
        jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x + i, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y + i, (int) resultado->getPosicion().y);
}

// ---------------------------------------------------------
// ---------------------- Fuera del mapa -------------------
// ---------------------------------------------------------

TEST(MovimientoJugadoresTests, adelanteFallaIrDerechaFuera) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia derecha
    //Poner 00 despues de la coma
    Coordinates angulo(1,0);
    Coordinates posicionIni(19,15);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAdelante dir;
    //act
    try {
        for (i = 0.0; i < 1.0; i+=step_size)
            jugador.mover(&dir);
    } catch (...){
    }
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y, (int) resultado->getPosicion().y);
}

TEST(MovimientoJugadoresTests, adelanteFallaIrArribaFuera) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia arriba
    //Poner 00 despues de la coma
    Coordinates angulo(0,1);
    Coordinates posicionIni(11,20);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAdelante dir;
    //act
    try {
        for (i = 0.0; i < 1.0; i+=step_size)
            jugador.mover(&dir);
    } catch (...){
    }
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y, (int) resultado->getPosicion().y);
}

TEST(MovimientoJugadoresTests, adelanteFallaIrIzquierdaFuera) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia izquierda
    //Poner 00 despues de la coma
    Coordinates angulo(-1,0);
    Coordinates posicionIni(0,15);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAdelante dir;
    //act
    try {
        for (i = 0.0; i < 1.0; i+=step_size)
            jugador.mover(&dir);
    } catch (...){
    }
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y, (int) resultado->getPosicion().y);
}

TEST(MovimientoJugadoresTests, adelanteFallaIrAbajoFuera) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia abajo
    //Poner 00 despues de la coma
    Coordinates angulo(0,-1);
    Coordinates posicionIni(11,0);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAdelante dir;
    //act
    try {
        for (i = 0.0; i < 1.0; i+=step_size)
            jugador.mover(&dir);
    } catch (...){
    }
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y, (int) resultado->getPosicion().y);
}

// ---------------------------------------------------------
// ------------- Colisiones entre posicionables ------------
// ---------------------------------------------------------

TEST(MovimientoJugadoresTests, adelanteFallaIrDerechaEncimaDeOtroJugador) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia derecha
    //Poner 00 despues de la coma
    Coordinates angulo(1,0);
    Coordinates posicionIni2(12,0);
    Jugador jugador2(posicionIni2, angulo,  mapa);
    Coordinates posicionIni(11,0);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAdelante dir;
    //act
    try {
        for (i = 0.0; i < 1.0; i+=step_size)
            jugador.mover(&dir);
    } catch (...){
    }
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y, (int) resultado->getPosicion().y);
}

// ---------------------------------------------------------
// ---------------- Giro hacia izquierda -------------------
// ---------------------------------------------------------

TEST(MovimientoJugadoresTests, giroAIzquierdaExitosoDesdeDerecha) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia derecha
    //Poner 00 despues de la coma
    Coordinates angulo(1,0);
    Coordinates angulo_rotado = angulo;

    Coordinates posicionIni(11,0);
    Jugador jugador(posicionIni, angulo, mapa);
    DirRotIzquierda dir;
    //act
    try {
        for (i = 0.0; i < 1.0; i+=step_size){
            jugador.mover(&dir);
            angulo_rotado.rotate(inc);
        }
    } catch (...){
    }
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y, (int) resultado->getPosicion().y);
    EXPECT_EQ (angulo_rotado.x, jugador.get_direction().x);
    EXPECT_EQ (angulo_rotado.y, jugador.get_direction().y);
}

TEST(MovimientoJugadoresTests, giroAIzquierdaExitosoDesdeArriba) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia arriba
    //Poner 00 despues de la coma
    Coordinates angulo(0,1);
    Coordinates angulo_rotado = angulo;
    Coordinates posicionIni(11,0);
    Jugador jugador(posicionIni, angulo, mapa);
    DirRotIzquierda dir;
    //act
    try {
        for (i = 0.0; i < 1.0; i+=step_size){
            jugador.mover(&dir);
            angulo_rotado.rotate(inc);
        }
    } catch (...){
    }
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y, (int) resultado->getPosicion().y);
    EXPECT_EQ (angulo_rotado.x, jugador.get_direction().x);
    EXPECT_EQ (angulo_rotado.y, jugador.get_direction().y);
}

TEST(MovimientoJugadoresTests, giroAIzquierdaExitosoDesdeIzquierda) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia izquierda
    //Poner 00 despues de la coma
    Coordinates angulo(-1,0);
    Coordinates angulo_rotado = angulo;
    Coordinates posicionIni(11,0);
    Jugador jugador(posicionIni, angulo, mapa);
    DirRotIzquierda dir;
    //act
    try {
        for (i = 0.0; i < 1.0; i+=step_size){
            jugador.mover(&dir);
            angulo_rotado.rotate(inc);
        }
    } catch (...){
    }
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y, (int) resultado->getPosicion().y);
    EXPECT_EQ (angulo_rotado.x, jugador.get_direction().x);
    EXPECT_EQ (angulo_rotado.y, jugador.get_direction().y);
}

TEST(MovimientoJugadoresTests, giroAIzquierdaExitosoDesdeAbajo) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia derecha
    //Poner 00 despues de la coma
    Coordinates angulo(0,-1);
    Coordinates angulo_rotado = angulo;
    Coordinates posicionIni(11,0);
    Jugador jugador(posicionIni, angulo, mapa);
    DirRotIzquierda dir;
    //act
    try {
        for (i = 0.0; i < 1.0; i+=step_size){
            jugador.mover(&dir);
            angulo_rotado.rotate(inc);
        }
    } catch (...){
    }
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y, (int) resultado->getPosicion().y);
    EXPECT_EQ (angulo_rotado.x, jugador.get_direction().x);
    EXPECT_EQ (angulo_rotado.y, jugador.get_direction().y);
}


// ---------------------------------------------------------
// ---------------- Giro hacia derecha -------------------
// ---------------------------------------------------------


TEST(MovimientoJugadoresTests, giroADerechaExitoso) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia derecha
    //Poner 00 despues de la coma
    Coordinates angulo(1,0);
    Coordinates angulo_rotado = angulo;
    Coordinates posicionIni(11,0);
    Jugador jugador(posicionIni, angulo, mapa);
    DirRotDerecha dir;
    //act
    try {
        for (i = 0.0; i < 1.0; i+=step_size){
            jugador.mover(&dir);
            angulo_rotado.rotate(-inc);
        }
    } catch (...){
    }
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y, (int) resultado->getPosicion().y);
    EXPECT_EQ (angulo_rotado.x, jugador.get_direction().x);
    EXPECT_EQ (angulo_rotado.y, jugador.get_direction().y);
}

TEST(MovimientoJugadoresTests, giroADerechaExitosoDesdeArriba) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia arriba
    //Poner 00 despues de la coma
    Coordinates angulo(0,1);
    Coordinates angulo_rotado = angulo;
    Coordinates posicionIni(11,0);
    Jugador jugador(posicionIni, angulo, mapa);
    DirRotDerecha dir;
    //act
    try {
        for (i = 0.0; i < 1.0; i+=step_size){
            jugador.mover(&dir);
            angulo_rotado.rotate(-inc);
        }
    } catch (...){
    }
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y, (int) resultado->getPosicion().y);
    EXPECT_EQ (angulo_rotado.x, jugador.get_direction().x);
    EXPECT_EQ (angulo_rotado.y, jugador.get_direction().y);
}

TEST(MovimientoJugadoresTests, giroADerechaExitosoDesdeIzquierda) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia izquierda
    //Poner 00 despues de la coma
    Coordinates angulo(-1,0);
    Coordinates angulo_rotado = angulo;
    Coordinates posicionIni(11,0);
    Jugador jugador(posicionIni, angulo, mapa);
    DirRotDerecha dir;
    //act
    try {
        for (i = 0.0; i < 1.0; i+=step_size){
            jugador.mover(&dir);
            angulo_rotado.rotate(-inc);
        }
    } catch (...){
    }
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y, (int) resultado->getPosicion().y);
    EXPECT_EQ (angulo_rotado.x, jugador.get_direction().x);
    EXPECT_EQ (angulo_rotado.y, jugador.get_direction().y);
}

TEST(MovimientoJugadoresTests, giroADerechaExitosoDesdeAbajo) {
    //arrange
    Mapa mapa(20,20);
    float i;
    //Mirando hacia derecha
    //Poner 00 despues de la coma
    Coordinates angulo(0,-1);
    Coordinates angulo_rotado = angulo;
    Coordinates posicionIni(11,0);
    Jugador jugador(posicionIni, angulo, mapa);
    DirRotDerecha dir;
    //act
    try {
        for (i = 0.0; i < 1.0; i+=step_size){
            jugador.mover(&dir);
            angulo_rotado.rotate(-inc);
        }
    } catch (...){
    }
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    //assert
    EXPECT_EQ ((int) posicionIni.x, (int) resultado->getPosicion().x);
    EXPECT_EQ ((int) posicionIni.y, (int) resultado->getPosicion().y);
    EXPECT_EQ (angulo_rotado.x, jugador.get_direction().x);
    EXPECT_EQ (angulo_rotado.y, jugador.get_direction().y);
}
