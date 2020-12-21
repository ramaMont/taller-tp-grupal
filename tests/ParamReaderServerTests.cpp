#include "gtest/gtest.h"
#include "ParamReaderServer.h"

TEST(ParamReaderServerTest, menosParams) {
    //arrange
    int result;
    try {
        char w1[] = "holis";
        char w2[] = "chauchis";
        char* args[] = { w1, w2 };
        ParamReaderServer serverPrueba(2, args);
        result = 0;
    } catch (...){
        result = 1;
    }
    //act
    //assert
    EXPECT_EQ (result, 1);
}

TEST(ParamReaderServerTest, cantCorrectaParams) {
    //arrange
    int result;
    try {
        char w1[] = "holis";
        char w2[] = "configuracion.yaml";
        char w3[] = "fname";
        char* args[] = { w1, w2, w3 };
        ParamReaderServer serverPrueba(3, args);
        result = 0;
    } catch (...){
        result = 1;
    }
    //act
    //assert
    EXPECT_EQ (result, 0);
}

TEST(ParamReaderServerTest, paramsDeMas) {
    //arrange
    int result;
    try {
        char w1[] = "holis";
        char w2[] = "chauchis";
        char w3[] = "fname";
        char w4[] = "fname";
        char* args[] = { w1, w2, w3, w4 };
        ParamReaderServer serverPrueba(4, args);
        result = 0;
    } catch (...){
        result = 1;
    }
    //act
    //assert
    EXPECT_EQ (result, 1);
}
