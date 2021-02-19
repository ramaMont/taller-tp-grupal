#include "EnvVariablesGetter.h"

std::string EnvVariablesGetter::getValue(std::string const &key) {
    char * val = getenv(key.c_str());
    return val == NULL ? std::string("") : std::string(val);
}

std::string EnvVariablesGetter::getDataPath() {
    return getValue("WOLFENSTEIN_DATA_PATH");
}

std::string EnvVariablesGetter::getTexturesPath() {
    return getValue("WOLFENSTEIN_TEXTURES_PATH");
}

std::string EnvVariablesGetter::getMapsPath() {
    return getValue("WOLFENSTEIN_MAPS_PATH");
}

std::string EnvVariablesGetter::getSoundsPath() {
    return getValue("WOLFENSTEIN_SOUNDS_PATH");
}

std::string EnvVariablesGetter::getMusicPath() {
    return getValue("WOLFENSTEIN_MUSIC_PATH");
}