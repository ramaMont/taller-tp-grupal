#include "EnvVariablesGetter.h"

std::string EnvVariablesGetter::getValue(std::string const &key) {
    // TODO: La idea principal era que esta clase lea
    // las variables de entorno, pero se complicó la creación
    // de las mismas en el archivo install.sh
    char * val = getenv(key.c_str());
    return val == NULL ? std::string("") : std::string(val);
}

std::string EnvVariablesGetter::getDataPath() {
    return "/var/Wolfenstein/data/";
}

std::string EnvVariablesGetter::getTexturesPath() {
    return "/var/Wolfenstein/data/textures/";
}

std::string EnvVariablesGetter::getMapsPath() {
    return "/var/Wolfenstein/data/maps/";
}

std::string EnvVariablesGetter::getSoundsPath() {
    return "/var/Wolfenstein/data/sounds/";
}

std::string EnvVariablesGetter::getMusicPath() {
    return "/var/Wolfenstein/data/background_music/";
}