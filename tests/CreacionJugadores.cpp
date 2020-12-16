#include "gtest/gtest.h"
#include <Jugador.h>
#include <Mapa.h>
#include <coordinates.h>
TEST(CreacionJugadoresTests, creacionExitosa) {
    //arrange
    Mapa mapa(20,20);
    Coordinates pos(2,5);
    Coordinates dir(0,0);
    Jugador jugador(pos, dir, mapa);
    //act
    Coordinates posicionResultado = mapa.obtenerPosicionableEn(pos)->get_position();
    //assert
    EXPECT_EQ (pos.x, posicionResultado.x);
    EXPECT_EQ (pos.y, posicionResultado.y);
}