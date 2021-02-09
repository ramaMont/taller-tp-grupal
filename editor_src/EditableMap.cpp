#include "EditableMap.h"
#include <algorithm>
#include <utility>
#include "yaml-cpp/yaml.h"

EditableMap::EditableMap(const int& flag,
                           const std::string& name,
                           const std::string& mapfile,
                           const int& rows, const int& columns)
                           : name(name), rows(rows), columns(columns) {
    if (flag == LOAD_FROM_FILE) {
        this->mapfile = mapfile;
        cargarMapaExistente();
    } else {
        if (rows > MAX_RC || columns > MAX_RC ||
            rows < MIN_Rc || columns < MIN_Rc)
            throw MapException("El número de rows y columns "
                "debe estar entre 10 y 40");
        this->mapfile = "../data/maps/" + name + ".yaml";
    }
}

void EditableMap::cargarMapaExistente() {
    YAML::Node map = YAML::LoadFile(mapfile);

    if ((!map["name"] || !map["rows"]) |
        (!map["columns"] || !map["elementos"])) {
        throw MapException("Mapa inválido!");
        return;
    }

    try {
        name = map["name"].as<std::string>();
        rows = map["rows"].as<int>();
        columns = map["columns"].as<int>();
    } catch (...) {
        throw MapException("El mapa contiene campos inválidos!");
    }

    if (rows > MAX_RC || columns > MAX_RC ||
        rows < MIN_Rc || columns < MIN_Rc) {
        throw MapException("El número de rows y columns "
               "debe estar entre 10 y 40");
    }

    for (int i=0; i < rows; i++) {
        for (int k=0; k < columns; k++) {
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

void EditableMap::saveMap() {
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "name";
    out << YAML::Value << name;
    out << YAML::Key << "rows";
    out << YAML::Value << rows;
    out << YAML::Key << "columns";
    out << YAML::Value << columns;
    out << YAML::Key << "elementos";
    out << YAML::BeginMap;
    for (auto const& element : mapa) {
        out << YAML::Key << element.first;
        out << YAML::Value << element.second;
    }
    out << YAML::EndMap;
    out << YAML::EndMap;
    std::ofstream file(mapfile);
    file << out.c_str();
}

void EditableMap::obtenerElemento(const std::string& posicion,
                                   std::string& elemento) {
    try {
        elemento = mapa[posicion];
    } catch (...) {
        std::cout << "Elemento no encontrado";
    }
}

void EditableMap::cargarElemento(const std::string& posicion,
                                  const std::string& elemento) {
    mapa.insert(std::pair<std::string, std::string>(posicion,
                                                    elemento));
}

void EditableMap::actualizarElemento(const std::string& posicion,
                                  const std::string& elemento) {
    mapa[posicion] = elemento;
}

void EditableMap::validarMapa() {
    validarParedes();
    validarPuertas();
}

void EditableMap::validarParedes() {
    // Validar que todos los bordes sean paredes.
    for (int c=0; c < columns; c++) {
        std::string pos_first_row = "pos_0_" + std::to_string(c);
        std::string pos_last_row = "pos_" + std::to_string(rows-1)
            + "_" + std::to_string(c);
        std::string element_first_row = mapa[pos_first_row];
        std::string element_last_row = mapa[pos_last_row];
        if ((!element_first_row.rfind("wall", 0) == 0) ||
            (!element_last_row.rfind("wall", 0) == 0)) {
            throw MapException("Los bordes del mapa deben ser paredes!");
        }
    }

    for (int f=0; f < rows; f++) {
        std::string pos_first_column = "pos_" + std::to_string(f) + "_0";
        std::string pos_last_column = "pos_" + std::to_string(f)
            + "_" + std::to_string(columns-1);
        std::string element_first_column = mapa[pos_first_column];
        std::string element_last_column = mapa[pos_last_column];
        if ((!element_first_column.rfind("wall", 0) == 0) ||
            (!element_last_column.rfind("wall", 0) == 0)) {
            throw MapException("Los bordes del mapa deben ser paredes!");
        }
    }
}

void EditableMap::validarPuertas() {
    for (int i=1; i < rows-1; i++) {
        for (int k=1; k < columns-1; k++) {
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

std::string EditableMap::getNombre() {
    return name;
}

int EditableMap::getColumnas() {
    return columns;
}

int EditableMap::getFilas() {
    return rows;
}

void EditableMap::limpiar() {
    mapa.clear();
}

void EditableMap::agregarFila() {
    rows += 1;
}

void EditableMap::eliminarFila() {
    rows -= 1;
}

void EditableMap::eliminarColumna() {
    columns -= 1;
}

void EditableMap::agregarColumna() {
    columns += 1;
}

EditableMap::~EditableMap() {
    limpiar();
}