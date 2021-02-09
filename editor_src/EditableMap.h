
#ifndef EditableMap_H
#define EditableMap_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "map_exceptions.h"

#define MAX_RC 40
#define MIN_Rc 10
#define LOAD_FROM_FILE 1
#define NEW_MAP 0

class EditableMap {
 public:
    EditableMap(const int& flag,
                 const std::string& name,
                 const std::string& mapfile,
                 const int& rows, const int& columns);
    ~EditableMap();
    void iniciarNuevoMapa(const int& rows, const int& columns);
    void cargarMapaExistente();
    void cargarElemento(const std::string& posicion,
                        const std::string& elemento);
    void actualizarElemento(const std::string& posicion,
                            const std::string& elemento);
    void obtenerElemento(const std::string& posicion,
                         std::string& elemento);
    void saveMap();
    void agregarFila();
    void agregarColumna();
    void eliminarFila();
    void eliminarColumna();
    void validarMapa();
    void validarParedes();
    void validarPuertas();
    int getColumnas();
    int getFilas();
    void limpiar();
    std::string getNombre();

 private:
    std::map<std::string, std::string> mapa;
    std::string mapfile;
    std::string name;
    int rows;
    int columns;
};

#endif // EditableMap_H