// #include "gtest/gtest.h"
// #include <Player.h>
// #include <Mapa.h>
// #include <coordinates.h>
// TEST(CreacionPlayeresTests, creacionExitosa) {
//     //arrange
//     Mapa mapa(20,20);
//     Coordinates pos(2,5);
//     Coordinates dir(0,0);
//     Player jugador(pos, dir, mapa);
//     //act
//     Coordinates posicionResultado = mapa.obtenerPosicionableEn(pos)->getPosicion();
//     //assert
//     EXPECT_EQ (pos.x, posicionResultado.x);
//     EXPECT_EQ (pos.y, posicionResultado.y);
// }