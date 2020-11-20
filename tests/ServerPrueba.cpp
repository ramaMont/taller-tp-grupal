#include "gtest/gtest.h"
#include "ServerPrueba.h"

TEST(serverPrueba_Doble, test1) {
    //arrange
    ServerPrueba serverPrueba;
    //act
    //assert
    EXPECT_EQ (serverPrueba.doble(0),  0);
    EXPECT_EQ (serverPrueba.doble(10), 20);
    EXPECT_EQ (serverPrueba.doble(50), 100);
}