#include "EditableMap.h"
#include <algorithm>
#include <utility>
#include "yaml-cpp/yaml.h"
#include <algorithm>

EditableMap::EditableMap(const int& flag,
                        const std::string& name,
                        const std::string& mapfile,
                        const int& rows, const int& columns)
                        : name(name), rows(rows), columns(columns) {
    if (flag == LOAD_FROM_FILE) {
        this->mapfile = mapfile;
        loadExistentMap();
    } else {
        if (rows > MAX_RC || columns > MAX_RC ||
            rows < MIN_Rc || columns < MIN_Rc)
            throw MapException("El número de rows y columns "
                "debe estar entre 10 y 40");
        this->mapfile = "../data/maps/" + name + ".yaml";
    }
}

void EditableMap::loadExistentMap() {
    YAML::Node map = YAML::LoadFile(mapfile);

    if ((!map["nombre"] || !map["filas"]) |
        (!map["columnas"] || !map["elementos"])) {
        throw MapException("Mapa inválido!");
        return;
    }

    try {
        name = map["nombre"].as<std::string>();
        rows = map["filas"].as<int>();
        columns = map["columnas"].as<int>();
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
            loadElement(pos, map["elementos"][pos].as<std::string>());
        }
    }
}

void EditableMap::saveMap() {
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "nombre";
    out << YAML::Value << name;
    out << YAML::Key << "filas";
    out << YAML::Value << rows;
    out << YAML::Key << "columnas";
    out << YAML::Value << columns;
    out << YAML::Key << "elementos";
    out << YAML::BeginMap;
    for (auto const& element : map) {
        std::string map_object = element.second;
        if ((map_object.rfind("i_", 0) == 0) ||
            (map_object.rfind("m_", 0) == 0) ||
            (map_object.rfind("g_", 0) == 0) ||
            (map_object.rfind("v_", 0) == 0)) {
            map_object = map_object.substr(2);
        }
        out << YAML::Key << element.first;
        out << YAML::Value << map_object;
    }
    out << YAML::EndMap;
    out << YAML::EndMap;
    std::ofstream file(mapfile);
    file << out.c_str();
}

void EditableMap::getElement(const std::string& position,
                                   std::string& element) {
    element = map[position];
    addCategory(element);
}

void EditableMap::addCategory(std::string& element) {
    // Algunos elementos, corresponden a categorias especificas.
    std::string guns[3] = {"machine_gun", "fire_canon", "rocket_launcher"};
    std::string mapable[5] = {"water", "barrel", "pilar", "table", "greenlight"};
    std::string vis[2] = {"door", "key_door"};
    std::string items[5] = {"key", "medicine", "trophie", "bullets", "food"};
    if (std::find(guns, guns + 3, element) != guns + 3)
        element = "g_" + element;
    if (std::find(mapable, mapable + 5, element) != mapable + 5)
        element = "m_" + element;
    if (std::find(vis, vis + 2, element) != vis + 2)
        element = "v_" + element;
    if (std::find(items, items + 5, element) != items + 5)
        element = "i_" + element;

}

void EditableMap::loadElement(const std::string& position,
                                  const std::string& element) {
    map.insert(std::pair<std::string, std::string>(position,
                                                    element));
}

void EditableMap::updateElement(const std::string& position,
                                  const std::string& element) {
    map[position] = element;
}

void EditableMap::validateMap() {
    validateWalls();
    validateDoors();
    validatePlayers();
}

void EditableMap::validateWalls() {
    // Validar que todos los bordes sean paredes.
    for (int c=0; c < columns; c++) {
        std::string pos_first_row = "pos_0_" + std::to_string(c);
        std::string pos_last_row = "pos_" + std::to_string(rows-1)
            + "_" + std::to_string(c);
        std::string element_first_row = map[pos_first_row];
        std::string element_last_row = map[pos_last_row];
        if ((!element_first_row.rfind("wall", 0) == 0) ||
            (!element_last_row.rfind("wall", 0) == 0)) {
            throw MapException("Los bordes del mapa deben ser paredes!");
        }
    }

    for (int f=0; f < rows; f++) {
        std::string pos_first_column = "pos_" + std::to_string(f) + "_0";
        std::string pos_last_column = "pos_" + std::to_string(f)
            + "_" + std::to_string(columns-1);
        std::string element_first_column = map[pos_first_column];
        std::string element_last_column = map[pos_last_column];
        if ((!element_first_column.rfind("wall", 0) == 0) ||
            (!element_last_column.rfind("wall", 0) == 0)) {
            throw MapException("Los bordes del mapa deben ser paredes!");
        }
    }
}

void EditableMap::validateDoors() {
    for (int i=1; i < rows-1; i++) {
        for (int k=1; k < columns-1; k++) {
            std::string pos = "pos_" + std::to_string(i) + "_" + std::to_string(k);
            std::string element = map[pos];
            if (element.rfind("door", 0) == 0) {
                std::string previous_row = "pos_" + std::to_string(i-1) + "_" + std::to_string(k);
                std::string next_row = "pos_" + std::to_string(i+1) + "_" + std::to_string(k);
                std::string previous_column = "pos_" + std::to_string(i) + "_" + std::to_string(k-1);
                std::string next_column = "pos_" + std::to_string(i) + "_" + std::to_string(k+1);
                std::string element_previous_row = map[previous_row];
                std::string element_next_row = map[next_row];
                std::string element_previous_column = map[previous_column];
                std::string element_next_column = map[next_column];
                if (!((element_previous_row.rfind("wall", 0) == 0) & (element_next_row.rfind("wall", 0) == 0)) & 
                    !((element_previous_column.rfind("wall", 0) == 0) & (element_next_column.rfind("wall", 0) == 0))) {
                    throw MapException("Las puertas deben estar rodeadas de paredes!");
                }
            }
        }
    }
}

void EditableMap::validatePlayers() {
    bool hasPlayer = false;
    for (int i=1; i < rows-1; i++) {
        for (int k=1; k < columns-1; k++) {
            std::string pos = "pos_" + std::to_string(i) + "_" + std::to_string(k);
            std::string element = map[pos];
            if (element.rfind("player", 0) == 0) {
                hasPlayer = true;
            }
        }
    }
    if (!hasPlayer)
        throw MapException("El mapa debe contener almenos 1 jugador!");
}

std::string EditableMap::getName() {
    return name;
}

int EditableMap::getColumns() {
    return columns;
}

int EditableMap::getRows() {
    return rows;
}

void EditableMap::clean() {
    map.clear();
}

void EditableMap::addRow() {
    rows += 1;
}

void EditableMap::deleteRow() {
    rows -= 1;
}

void EditableMap::deleteColumn() {
    columns -= 1;
}

void EditableMap::addColumn() {
    columns += 1;
}

EditableMap::~EditableMap() {
    clean();
}