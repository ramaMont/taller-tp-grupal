#include "EnvVariablesGetter.h"

std::string EnvVariablesGetter::getValue(std::string const &key) {
    // TODO: La idea principal era que esta clase lea
    // las variables de entorno, pero se complicó la creación
    // de las mismas en el archivo install.sh
    char * val = getenv(key.c_str());
    return val == NULL ? std::string("") : std::string(val);
}

std::string EnvVariablesGetter::getDataPath() {
    std::string home(getenv("HOME"));
    return home + "/.Wolfenstein/data/";
}

std::string EnvVariablesGetter::getTexturesPath() {
    std::string home(getenv("HOME"));
    return home + "/.Wolfenstein/data/textures/";
}

std::string EnvVariablesGetter::getMapsPath() {
    std::string home(getenv("HOME"));
    return home + "/.Wolfenstein/data/maps/";
}

std::string EnvVariablesGetter::getSoundsPath() {
    std::string home(getenv("HOME"));
    return home + "/.Wolfenstein/data/sounds/";
}

std::string EnvVariablesGetter::getMusicPath() {
    std::string home(getenv("HOME"));
    return home + "/.Wolfenstein/data/background_music/";
}