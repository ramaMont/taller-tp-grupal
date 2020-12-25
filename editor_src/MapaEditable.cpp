#include "MapaEditable.h"
#include <algorithm>
#include <utility>
#include "yaml-cpp/yaml.h"

void MapaEditable::cargarMapaExistente() {
    // TODO: meter este comportamiento en una clase. (RAII)
    YAML::Node map = YAML::LoadFile(archivo_mapa);

    if (!map["nombre"] | !map["filas"] |
        !map["columnas"] | !map["elementos"]) {
        std::cout << "Invalid map" << std::endl;
        return;
    }

    nombre = map["nombre"].as<std::string>();
    filas = map["filas"].as<int>();
    columnas = map["columnas"].as<int>();

    for (int i=0; i < filas; i++) {
        for (int k=0; k < columnas; k++) {
            std::string pos = "pos_" + std::to_string(i) +
                "_" + std::to_string(k);
            if (!map["elementos"][pos]) {
                std::cout << "Error: posicion " << pos
                    << "no encontrada" << std::endl;
                return;
            }
            cargarElemento(pos, map["elementos"][pos].as<std::string>());
        }
    }
}

void MapaEditable::guardarMapa() {
    // TODO: meter este comportamiento en una clase. (RAII)
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "nombre";
    out << YAML::Value << nombre;
    out << YAML::Key << "filas";
    out << YAML::Value << filas;
    out << YAML::Key << "columnas";
    out << YAML::Value << columnas;
    out << YAML::Key << "elementos";
    out << YAML::BeginMap;
    for (auto const& element : mapa) {
        out << YAML::Key << element.first;
        out << YAML::Value << element.second;
    }
    out << YAML::EndMap;
    out << YAML::EndMap;
    std::ofstream file(archivo_mapa);
    file << out.c_str();
}

void MapaEditable::obtenerElemento(const std::string& posicion,
                                   std::string& elemento) {
    try {
        elemento = mapa[posicion];
    } catch (...) {
        // TODO: Agregar excepcion y lanzarla.
        std::cout << "Elemento no encontrado";
    }
}

void MapaEditable::cargarElemento(const std::string& posicion,
                                  const std::string& elemento) {
    mapa.insert(std::pair<std::string, std::string>(posicion,
                                                    elemento));
}

void MapaEditable::actualizarElemento(const std::string& posicion,
                                  const std::string& elemento) {
    mapa[posicion] = elemento;
}

std::string MapaEditable::getNombre() {
    return nombre;
}

int MapaEditable::getColumnas() {
    return columnas;
}

int MapaEditable::getFilas() {
    return filas;
}

void MapaEditable::limpiar() {
    mapa.clear();
}

void MapaEditable::agregarFila() {
    filas += 1;
}

void MapaEditable::eliminarFila() {
    filas -= 1;
}

void MapaEditable::eliminarColumna() {
    columnas -= 1;
}

void MapaEditable::agregarColumna() {
    columnas += 1;
}

MapaEditable::~MapaEditable() {
    limpiar();
}