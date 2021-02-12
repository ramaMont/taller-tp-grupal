// #include "gtest/gtest.h"
// #include <Player.h>
// #include <ServerMap.h>
// #include <Direccion.h>
// #include <coordinates.h>
// #include <Posicionable.h>

// #include <cmath>

// static float inc = 0.15;
// static const float step_size = 0.15;
// //-------------------- Hacia adelante ------------------------------------
// TEST(MovimientoPlayeresTests, adelanteExitosoDesdeDerecha) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     bool lugar_vacio = false;
//     //Mirando hacia la derecha
//     Coordinates angulo(1,0);
//     Coordinates posicionIni(11, 15);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAdelante dir;
//     //act
//     for (i = 0.0; i < 1.0; i+=step_size)
//         jugador.mover(&dir);
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());

//     Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
//     if (vacio == nullptr)
//         lugar_vacio = true;
//     //assert
//     EXPECT_EQ (lugar_vacio, true);
//     EXPECT_EQ (floor(posicionIni.x + i), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y), floor(resultado->getPosicion().y));
// }
// TEST(MovimientoPlayeresTests, adelanteExitosoDesdeArriba) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     bool lugar_vacio = false;
//     //Mirando hacia la arriba
//     Coordinates angulo(0,1);
//     Coordinates posicionIni(11, 15);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAdelante dir;
//     for (i = 0.0; i < 1.0; i+=step_size)
//         jugador.mover(&dir);
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
//     if (vacio == nullptr)
//         lugar_vacio = true;
//     //assert
//     EXPECT_EQ (lugar_vacio, true);
//     EXPECT_EQ (floor(posicionIni.x), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y + i), floor(resultado->getPosicion().y));
// }
// TEST(MovimientoPlayeresTests, adelanteExitosoDesdeIzquierda) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     bool lugar_vacio = false;
//     //Mirando hacia la izquierda
//     //Poner 00 despues de la coma
//     Coordinates angulo(-1,0);
//     Coordinates posicionIni(11, 15);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAdelante dir;
//     for (i = 0.0; i < 1.0; i+=step_size)
//         jugador.mover(&dir);
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
//     if (vacio == nullptr)
//         lugar_vacio = true;
//     //assert
//     EXPECT_EQ (lugar_vacio, true);
//     EXPECT_EQ (floor(posicionIni.x - i), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y), floor(resultado->getPosicion().y));
// }
// TEST(MovimientoPlayeresTests, adelanteExitosoDesdeAbajo) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     bool lugar_vacio = false;
//     //Mirando hacia abajo
//     //Poner 00 despues de la coma
//     Coordinates angulo(0,-1);
//     Coordinates posicionIni(11, 15);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAdelante dir;
//     for (i = 0.0; i < 1.0; i+=step_size)
//         jugador.mover(&dir);
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
//     if (vacio == nullptr)
//         lugar_vacio = true;
//     //assert
//     EXPECT_EQ (lugar_vacio, true);
//     EXPECT_EQ (floor(posicionIni.x),  floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y - i), floor(resultado->getPosicion().y));
// }
// TEST(MovimientoPlayeresTests, adelanteExitosoDesdeDerechaArriba) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     bool lugar_vacio = false;
//     //Mirando hacia arriba y a la derecha
//     //Poner 00 despues de la coma
//     Coordinates angulo(1,1);
//     Coordinates posicionIni(11, 15);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAdelante dir;
//     for (i = 0.0; i < 1.0; i+=step_size)
//         jugador.mover(&dir);
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
//     if (vacio == nullptr)
//         lugar_vacio = true;
//     //assert
//     EXPECT_EQ (lugar_vacio, true);
//     EXPECT_EQ (floor(posicionIni.x + i), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y + i), floor(resultado->getPosicion().y));
// }
// TEST(MovimientoPlayeresTests, adelanteExitosoDesdeDerechaAbajo) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     bool lugar_vacio = false;
//     //Mirando hacia abajo y hacia la derecha
//     //Poner 00 despues de la coma
//     Coordinates angulo(1,-1);
//     Coordinates posicionIni(11, 15);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAdelante dir;
//     for (i = 0.0; i < 1.0; i+=step_size)
//         jugador.mover(&dir);
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
//     if (vacio == nullptr)
//         lugar_vacio = true;
//     //assert
//     EXPECT_EQ (lugar_vacio, true);
//     EXPECT_EQ (floor(posicionIni.x + i), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y - i), floor(resultado->getPosicion().y));
// }
// TEST(MovimientoPlayeresTests, adelanteExitosoDesdeIzquierdaArriba) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     bool lugar_vacio = false;
//     //Mirando hacia arriba y hacia la izquierda
//     //Poner 00 despues de la coma
//     Coordinates angulo(-1,1);
//     Coordinates posicionIni(11, 15);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAdelante dir;
//     for (i = 0.0; i < 1.0; i+=step_size)
//         jugador.mover(&dir);
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
//     if (vacio == nullptr)
//         lugar_vacio = true;
//     //assert
//     EXPECT_EQ (lugar_vacio, true);
//     EXPECT_EQ (floor(posicionIni.x - i), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y + i), floor(resultado->getPosicion().y));
// }
// TEST(MovimientoPlayeresTests, adelanteExitosoDesdeIzquierdaAbajo) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     bool lugar_vacio = false;
//     //Mirando hacia abajo y hacia la izquierda
//     //Poner 00 despues de la coma
//     Coordinates angulo(-1,-1);
//     Coordinates posicionIni(11, 15);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAdelante dir;
//     for (i = 0.0; i < 1.0; i+=step_size)
//         jugador.mover(&dir);
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
//     if (vacio == nullptr)
//         lugar_vacio = true;
//     //assert
//     EXPECT_EQ (lugar_vacio, true);
//     EXPECT_EQ (floor(posicionIni.x - i), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y - i), floor(resultado->getPosicion().y));
// }

// // ---------------------------------------------------------
// // ---------------------- Hacia atras ----------------------
// // ---------------------------------------------------------

// TEST(MovimientoPlayeresTests, atrasExitosoDesdeDerecha) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia la derecha
//     Coordinates angulo(1,0);
//     Coordinates posicionIni(11, 15);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAtras dir;
//     for (i = 0.0; i < 1.0; i+=step_size)
//         jugador.mover(&dir);
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert
//     EXPECT_EQ (floor(posicionIni.x - i), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y), floor(resultado->getPosicion().y));    
// }
// TEST(MovimientoPlayeresTests, atrasExitosoDesdeArriba) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia la arriba
//     Coordinates angulo(0,1);
//     Coordinates posicionIni(11, 15);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAtras dir;
//     for (i = 0.0; i < 1.0; i+=step_size)
//         jugador.mover(&dir);
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert
//     EXPECT_EQ (floor(posicionIni.x), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y - i), floor(resultado->getPosicion().y));
// }
// TEST(MovimientoPlayeresTests, atrasExitosoDesdeIzquierda) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia la izquierda
//     //Poner 00 despues de la coma
//     Coordinates angulo(-1,0);
//     Coordinates posicionIni(11, 15);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAtras dir;
//     for (i = 0.0; i < 1.0; i+=step_size)
//         jugador.mover(&dir);
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert
//     EXPECT_EQ (floor(posicionIni.x + i), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y), floor(resultado->getPosicion().y));  
// }
// TEST(MovimientoPlayeresTests, atrasExitosoDesdeAbajo) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia abajo
//     //Poner 00 despues de la coma
//     Coordinates angulo(0,-1);
//     Coordinates posicionIni(11, 15);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAtras dir;
//     for (i = 0.0; i < 1.0; i+=step_size)
//         jugador.mover(&dir);
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert
//     EXPECT_EQ (floor(posicionIni.x), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y + i), floor(resultado->getPosicion().y));
// }
// TEST(MovimientoPlayeresTests, atrasExitosoDesdeDerechaArriba) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia arriba y a la derecha
//     //Poner 00 despues de la coma
//     Coordinates angulo(1,1);
//     Coordinates posicionIni(11, 15);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAtras dir;
//     for (i = 0.0; i < 1.0; i+=step_size)
//         jugador.mover(&dir);
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert
//     EXPECT_EQ (floor(posicionIni.x - i), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y - i), floor(resultado->getPosicion().y));    
// }
// TEST(MovimientoPlayeresTests, atrasExitosoDesdeDerechaAbajo) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia abajo y hacia la derecha
//     //Poner 00 despues de la coma
//     Coordinates angulo(1,-1);
//     Coordinates posicionIni(11, 15);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAtras dir;
//     for (i = 0.0; i < 1.0; i+=step_size)
//         jugador.mover(&dir);
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert
//     EXPECT_EQ (floor(posicionIni.x - i), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y + i), floor(resultado->getPosicion().y));
// }
// TEST(MovimientoPlayeresTests, atrasExitosoDesdeIzquierdaArriba) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia arriba y hacia la izquierda
//     //Poner 00 despues de la coma
//     Coordinates angulo(-1,1);
//     Coordinates posicionIni(11, 15);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAtras dir;
//     for (i = 0.0; i < 1.0; i+=step_size)
//         jugador.mover(&dir);
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert
//     EXPECT_EQ (floor(posicionIni.x + i), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y - i), floor(resultado->getPosicion().y));
// }
// TEST(MovimientoPlayeresTests, atrasExitosoDesdeIzquierdaAbajo) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia abajo y hacia la izquierda
//     //Poner 00 despues de la coma
//     Coordinates angulo(-1,-1);
//     Coordinates posicionIni(11, 15);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAtras dir;
//     for (i = 0.0; i < 1.0; i+=step_size)
//         jugador.mover(&dir);
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert
//     EXPECT_EQ (floor(posicionIni.x + i), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y + i), floor(resultado->getPosicion().y));
// }

// // ---------------------------------------------------------
// // ---------------------- Fuera del mapa -------------------
// // ---------------------------------------------------------

// TEST(MovimientoPlayeresTests, adelanteFallaIrDerechaFuera) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia derecha
//     //Poner 00 despues de la coma
//     Coordinates angulo(1,0);
//     Coordinates posicionIni(19,15);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAdelante dir;
//     //act
//     try {
//         for (i = 0.0; i < 1.0; i+=step_size)
//             jugador.mover(&dir);
//     } catch (...){
//     }
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert
//     EXPECT_EQ (floor(posicionIni.x), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y), floor(resultado->getPosicion().y));    
// }

// TEST(MovimientoPlayeresTests, adelanteFallaIrArribaFuera) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia arriba
//     //Poner 00 despues de la coma
//     Coordinates angulo(0,1);
//     Coordinates posicionIni(11,20);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAdelante dir;
//     //act
//     try {
//         for (i = 0.0; i < 1.0; i+=step_size)
//             jugador.mover(&dir);
//     } catch (...){
//     }
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert

//     EXPECT_EQ (floor(posicionIni.x), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y), floor(resultado->getPosicion().y)); 
// }

// TEST(MovimientoPlayeresTests, adelanteFallaIrIzquierdaFuera) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia izquierda
//     //Poner 00 despues de la coma
//     Coordinates angulo(-1,0);
//     Coordinates posicionIni(0,15);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAdelante dir;
//     //act
//     try {
//         for (i = 0.0; i < 1.0; i+=step_size)
//             jugador.mover(&dir);
//     } catch (...){
//     }
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert
//     EXPECT_EQ (floor(posicionIni.x), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y), floor(resultado->getPosicion().y)); 
// }

// TEST(MovimientoPlayeresTests, adelanteFallaIrAbajoFuera) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia abajo
//     //Poner 00 despues de la coma
//     Coordinates angulo(0,-1);
//     Coordinates posicionIni(11,0);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAdelante dir;
//     //act
//     try {
//         for (i = 0.0; i < 1.0; i+=step_size)
//             jugador.mover(&dir);
//     } catch (...){
//     }
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert
//     EXPECT_EQ (floor(posicionIni.x), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y), floor(resultado->getPosicion().y)); 
// }

// // ---------------------------------------------------------
// // ------------- Colisiones entre posicionables ------------
// // ---------------------------------------------------------

// TEST(MovimientoPlayeresTests, adelanteFallaIrDerechaEncimaDeOtroPlayer) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia derecha
//     //Poner 00 despues de la coma
//     Coordinates angulo(1,0);
//     Coordinates posicionIni2(12,0);
//     Player jugador2(posicionIni2, angulo,  mapa);
//     Coordinates posicionIni(11,0);
//     Player jugador(posicionIni, angulo, mapa);
//     DirAdelante dir;
//     //act
//     try {
//         for (i = 0.0; i < 1.0; i+=step_size)
//             jugador.mover(&dir);
//     } catch (...){
//     }
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert
//     EXPECT_EQ (floor(posicionIni.x), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y), floor(resultado->getPosicion().y)); 
// }

// // ---------------------------------------------------------
// // ---------------- Giro hacia izquierda -------------------
// // ---------------------------------------------------------

// // A partir del sexto  dígito, divergen muy levemente 
// // algunos floats con respecto a la rotacion pero se decidió obviarlos
// int first_n_decimals(float number){
//     return number*(pow(10,6));
// }


// TEST(MovimientoPlayeresTests, giroAIzquierdaExitosoDesdeDerecha) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia derecha
//     //Poner 00 despues de la coma
//     Coordinates angulo(1,0);
//     Coordinates angulo_rotado = angulo;

//     Coordinates posicionIni(11,0);
//     Player jugador(posicionIni, angulo, mapa);
//     DirRotIzquierda dir;
//     //act
//     try {
//         for (i = 0.0; i < 1.0; i+=step_size){
//             jugador.mover(&dir);
//             angulo_rotado.rotate(inc);
//         }
//     } catch (...){
//     }
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert
    
//     EXPECT_EQ (floor(posicionIni.x), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y), floor(resultado->getPosicion().y)); 
//     EXPECT_EQ (first_n_decimals(angulo_rotado.x), first_n_decimals(jugador.get_direction().x));
//     EXPECT_EQ (first_n_decimals(angulo_rotado.y), first_n_decimals(jugador.get_direction().y));
// }

// TEST(MovimientoPlayeresTests, giroAIzquierdaExitosoDesdeArriba) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia arriba
//     //Poner 00 despues de la coma
//     Coordinates angulo(0,1);
//     Coordinates angulo_rotado = angulo;
//     Coordinates posicionIni(11,0);
//     Player jugador(posicionIni, angulo, mapa);
//     DirRotIzquierda dir;
//     //act
//     try {
//         for (i = 0.0; i < 1.0; i+=step_size){
//             jugador.mover(&dir);
//             angulo_rotado.rotate(inc);
//         }
//     } catch (...){
//     }
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert
//     EXPECT_EQ (floor(posicionIni.x), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y), floor(resultado->getPosicion().y)); 
//     EXPECT_EQ (first_n_decimals(angulo_rotado.x), first_n_decimals(jugador.get_direction().x));
//     EXPECT_EQ (first_n_decimals(angulo_rotado.y), first_n_decimals(jugador.get_direction().y));
// }

// TEST(MovimientoPlayeresTests, giroAIzquierdaExitosoDesdeIzquierda) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia izquierda
//     //Poner 00 despues de la coma
//     Coordinates angulo(-1,0);
//     Coordinates angulo_rotado = angulo;
//     Coordinates posicionIni(11,0);
//     Player jugador(posicionIni, angulo, mapa);
//     DirRotIzquierda dir;
//     //act
//     try {
//         for (i = 0.0; i < 1.0; i+=step_size){
//             jugador.mover(&dir);
//             angulo_rotado.rotate(inc);
//         }
//     } catch (...){
//     }
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert
//     EXPECT_EQ (floor(posicionIni.x), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y), floor(resultado->getPosicion().y)); 
//     EXPECT_EQ (first_n_decimals(angulo_rotado.x), first_n_decimals(jugador.get_direction().x));
//     EXPECT_EQ (first_n_decimals(angulo_rotado.y), first_n_decimals(jugador.get_direction().y));
// }

// TEST(MovimientoPlayeresTests, giroAIzquierdaExitosoDesdeAbajo) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia derecha
//     //Poner 00 despues de la coma
//     Coordinates angulo(0,-1);
//     Coordinates angulo_rotado = angulo;
//     Coordinates posicionIni(11,0);
//     Player jugador(posicionIni, angulo, mapa);
//     DirRotIzquierda dir;
//     //act
//     try {
//         for (i = 0.0; i < 1.0; i+=step_size){
//             jugador.mover(&dir);
//             angulo_rotado.rotate(inc);
//         }
//     } catch (...){
//     }
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert
//     EXPECT_EQ (floor(posicionIni.x), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y), floor(resultado->getPosicion().y)); 
//     EXPECT_EQ (first_n_decimals(angulo_rotado.x), first_n_decimals(jugador.get_direction().x));
//     EXPECT_EQ (first_n_decimals(angulo_rotado.y), first_n_decimals(jugador.get_direction().y));
// }


// // ---------------------------------------------------------
// // ---------------- Giro hacia derecha -------------------
// // ---------------------------------------------------------


// TEST(MovimientoPlayeresTests, giroADerechaExitoso) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia derecha
//     //Poner 00 despues de la coma
//     Coordinates angulo(1,0);
//     Coordinates angulo_rotado = angulo;
//     Coordinates posicionIni(11,0);
//     Player jugador(posicionIni, angulo, mapa);
//     DirRotDerecha dir;
//     //act
//     try {
//         for (i = 0.0; i < 1.0; i+=step_size){
//             jugador.mover(&dir);
//             angulo_rotado.rotate(-inc);
//         }
//     } catch (...){
//     }
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert
//     EXPECT_EQ (floor(posicionIni.x), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y), floor(resultado->getPosicion().y)); 
//     EXPECT_EQ (first_n_decimals(angulo_rotado.x), first_n_decimals(jugador.get_direction().x));
//     EXPECT_EQ (first_n_decimals(angulo_rotado.y), first_n_decimals(jugador.get_direction().y));
// }

// TEST(MovimientoPlayeresTests, giroADerechaExitosoDesdeArriba) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia arriba
//     //Poner 00 despues de la coma
//     Coordinates angulo(0,1);
//     Coordinates angulo_rotado = angulo;
//     Coordinates posicionIni(11,0);
//     Player jugador(posicionIni, angulo, mapa);
//     DirRotDerecha dir;
//     //act
//     try {
//         for (i = 0.0; i < 1.0; i+=step_size){
//             jugador.mover(&dir);
//             angulo_rotado.rotate(-inc);
//         }
//     } catch (...){
//     }
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert
//     EXPECT_EQ (floor(posicionIni.x), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y), floor(resultado->getPosicion().y)); 
//     EXPECT_EQ (first_n_decimals(angulo_rotado.x), first_n_decimals(jugador.get_direction().x));
//     EXPECT_EQ (first_n_decimals(angulo_rotado.y), first_n_decimals(jugador.get_direction().y));
// }

// TEST(MovimientoPlayeresTests, giroADerechaExitosoDesdeIzquierda) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia izquierda
//     //Poner 00 despues de la coma
//     Coordinates angulo(-1,0);
//     Coordinates angulo_rotado = angulo;
//     Coordinates posicionIni(11,0);
//     Player jugador(posicionIni, angulo, mapa);
//     DirRotDerecha dir;
//     //act
//     try {
//         for (i = 0.0; i < 1.0; i+=step_size){
//             jugador.mover(&dir);
//             angulo_rotado.rotate(-inc);
//         }
//     } catch (...){
//     }
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert
//     EXPECT_EQ (floor(posicionIni.x), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y), floor(resultado->getPosicion().y)); 
//     EXPECT_EQ (first_n_decimals(angulo_rotado.x), first_n_decimals(jugador.get_direction().x));
//     EXPECT_EQ (first_n_decimals(angulo_rotado.y), first_n_decimals(jugador.get_direction().y));
// }

// TEST(MovimientoPlayeresTests, giroADerechaExitosoDesdeAbajo) {
//     //arrange
//     ServerMap mapa(20,20);
//     float i;
//     //Mirando hacia derecha
//     //Poner 00 despues de la coma
//     Coordinates angulo(0,-1);
//     Coordinates angulo_rotado = angulo;
//     Coordinates posicionIni(11,0);
//     Player jugador(posicionIni, angulo, mapa);
//     DirRotDerecha dir;
//     //act
//     try {
//         for (i = 0.0; i < 1.0; i+=step_size){
//             jugador.mover(&dir);
//             angulo_rotado.rotate(-inc);
//         }
//     } catch (...){
//     }
//     Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
//     //assert
//     EXPECT_EQ (floor(posicionIni.x), floor(resultado->getPosicion().x));
//     EXPECT_EQ (floor(posicionIni.y), floor(resultado->getPosicion().y)); 
//     EXPECT_EQ (first_n_decimals(angulo_rotado.x), first_n_decimals(jugador.get_direction().x));
//     EXPECT_EQ (first_n_decimals(angulo_rotado.y), first_n_decimals(jugador.get_direction().y));
// }
