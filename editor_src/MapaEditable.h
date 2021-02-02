
#ifndef MAPAEDITABLE_H
#define MAPAEDITABLE_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "map_exceptions.h"

#define MAX_FC 40
#define MIN_FC 10
#define CARGAR_DESDE_ARCHIVO 1
#define NUEVO_MAPA 0

class MapaEditable {
 public:
    MapaEditable(const int& flag,
                 const std::string& nombre,
                 const std::string& archivo_mapa,
                 const int& filas, const int& columnas);
    ~MapaEditable();
    void iniciarNuevoMapa(const int& rows, const int& columns);
    void cargarMapaExistente();
    void cargarElemento(const std::string& posicion,
                        const std::string& elemento);
    void actualizarElemento(const std::string& posicion,
                            const std::string& elemento);
    void obtenerElemento(const std::string& posicion,
                         std::string& elemento);
    void guardarMapa();
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
    std::string archivo_mapa;
    std::string nombre;
    int filas;
    int columnas;
};

#endif // MAPAEDITABLE_H