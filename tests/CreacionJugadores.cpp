#include "gtest/gtest.h"
#include "Jugador.h"
#include "Mapa.h"

TEST(CreacionJugadoresTests, creacionExitosa) {
    //arrange
    Mapa mapa;
    Posicion posicion(11,15);
    Jugador jugador(posicion, mapa);
    //act
    Posicion posicionResultado = mapa.obtenerPosicionableEn(posicion)->getPosicion();
    //assert
    EXPECT_EQ (posicion.getPosX(), posicionResultado.getPosX());
    EXPECT_EQ (posicion.getPosY(), posicionResultado.getPosY());
}