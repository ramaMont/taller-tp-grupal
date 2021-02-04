#include "MapaEditable.h"
#include <algorithm>
#include <utility>
#include "yaml-cpp/yaml.h"

MapaEditable::MapaEditable(const int& flag,
                           const std::string& nombre,
                           const std::string& archivo_mapa,
                           const int& filas, const int& columnas)
                           : nombre(nombre), filas(filas), columnas(columnas) {
    if (flag == CARGAR_DESDE_ARCHIVO) {
        this->archivo_mapa = archivo_mapa;
        cargarMapaExistente();
    } else {
        if (filas > MAX_FC || columnas > MAX_FC ||
            filas < MIN_FC || columnas < MIN_FC)
            throw MapException("El número de filas y columnas "
                "debe estar entre 10 y 40");
        this->archivo_mapa = "../data/maps/" + nombre + ".yaml";
    }
}

void MapaEditable::cargarMapaExistente() {
    YAML::Node map = YAML::LoadFile(archivo_mapa);

    if ((!map["nombre"] || !map["filas"]) |
        (!map["columnas"] || !map["elementos"])) {
        throw MapException("Mapa inválido!");
        return;
    }

    try {
        nombre = map["nombre"].as<std::string>();
        filas = map["filas"].as<int>();
        columnas = map["columnas"].as<int>();
    } catch (...) {
        throw MapException("El mapa contiene campos inválidos!");
    }

    if (filas > MAX_FC || columnas > MAX_FC ||
        filas < MIN_FC || columnas < MIN_FC) {
        throw MapException("El número de filas y columnas "
               "debe estar entre 10 y 40");
    }

    for (int i=0; i < filas; i++) {
        for (int k=0; k < columnas; k++) {
            std::string pos = "pos_" + std::to_string(i) +
                "_" + std::to_string(k);
            if (!map["elementos"][pos]) {
                throw MapException("El mapa contiene posiciones faltantes!");
                return;
            }
            cargarElemento(pos, map["elementos"][pos].as<std::string>());
        }
    }
}

void MapaEditable::guardarMapa() {
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

void MapaEditable::validarMapa() {
    validarParedes();
    validarPuertas();
}

void MapaEditable::validarParedes() {
    // Validar que todos los bordes sean paredes.
    for (int c=0; c < columnas; c++) {
        std::string pos_first_row = "pos_0_" + std::to_string(c);
        std::string pos_last_row = "pos_" + std::to_string(filas-1)
            + "_" + std::to_string(c);
        std::string element_first_row = mapa[pos_first_row];
        std::string element_last_row = mapa[pos_last_row];
        if ((!element_first_row.rfind("wall", 0) == 0) ||
            (!element_last_row.rfind("wall", 0) == 0)) {
            throw MapException("Los bordes del mapa deben ser paredes!");
        }
    }

    for (int f=0; f < filas; f++) {
        std::string pos_first_column = "pos_" + std::to_string(f) + "_0";
        std::string pos_last_column = "pos_" + std::to_string(f)
            + "_" + std::to_string(columnas-1);
        std::string element_first_column = mapa[pos_first_column];
        std::string element_last_column = mapa[pos_last_column];
        if ((!element_first_column.rfind("wall", 0) == 0) ||
            (!element_last_column.rfind("wall", 0) == 0)) {
            throw MapException("Los bordes del mapa deben ser paredes!");
        }
    }
}

void MapaEditable::validarPuertas() {
    for (int i=1; i < filas-1; i++) {
        for (int k=1; k < columnas-1; k++) {
            std::string pos = "pos_" + std::to_string(i) + "_" + std::to_string(k);
            std::string elemento = mapa[pos];
            if (elemento.rfind("door", 0) == 0) {
                std::string previous_row = "pos_" + std::to_string(i-1) + "_" + std::to_string(k);
                std::string next_row = "pos_" + std::to_string(i+1) + "_" + std::to_string(k);
                std::string previous_column = "pos_" + std::to_string(i) + "_" + std::to_string(k-1);
                std::string next_column = "pos_" + std::to_string(i) + "_" + std::to_string(k+1);
                std::string element_previous_row = mapa[previous_row];
                std::string element_next_row = mapa[next_row];
                std::string element_previous_column = mapa[previous_column];
                std::string element_next_column = mapa[next_column];
                if (!((element_previous_row.rfind("wall", 0) == 0) & (element_next_row.rfind("wall", 0) == 0)) & 
                    !((element_previous_column.rfind("wall", 0) == 0) & (element_next_column.rfind("wall", 0) == 0))) {
                    throw MapException("Las puertas deben estar rodeadas de paredes!");
                }
            }
        }
    }
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