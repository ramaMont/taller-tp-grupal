#include "MapaEditable.h"
#include <algorithm>
#include <utility>

void MapaEditable::iniciarNuevoMapa(const int& rows, const int& columns) {
}

void MapaEditable::cargarMapaExistente() {
    std::ifstream file;
    file.open(archivo_mapa);
    if (file.is_open()) {
        try {
            std::string map_name, cols, rows, pos, element, key;
            file >> key >> map_name;
            file >> key >> rows;
            file >> key >> cols;
            file >> key;
            std::cout << map_name << " " << rows << " " << cols << std::endl;
            while (file >> key) {
                file >> pos;
                pos.pop_back();
                file >> element;
                cargarElemento(pos, element);
                pos.clear();
                element.clear();
            }
            nombre = map_name;
            columnas = std::stoi(cols);
            filas = std::stoi(rows);
        } catch (...) {
            std::cout << "Error reading map file";
        }
    }
    file.close();
}

void MapaEditable::guardarMapa() {
    std::ofstream file;
    file.open(archivo_mapa);
    file << "nombre: " << nombre << std::endl;
    file << "filas: " << filas << std::endl;
    file << "columnas: " << columnas << std::endl;
    for (auto const& element : mapa) {
        file << element.first << ": " << element.second << std::endl;
    }
    file.close();
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

int MapaEditable::getColumnas() {
    return columnas;
}

int MapaEditable::getFilas() {
    return filas;
}
