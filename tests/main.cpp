#include "gtest/gtest.h"
#include "ParamReaderServer.h"

int main(int argc, char **argv) {
	char w1[] = "";
    char w2[] = "";
    char w3[] = "configuracion.yaml";
    char* args[] = {w1, w2, w3};
	ParamReaderServer(3, args);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
