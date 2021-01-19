#include <iostream>
#include <string>
#include <map>
#include <fstream>

#define MAX_FC 40
#define MIN_FC 10
#define CARGAR_DESDE_ARCHIVO 1
#define NUEVO_MAPA 0

#ifndef MAPAEDITABLE_H
#define MAPAEDITABLE_H

class MapaEditable {
 public:
    MapaEditable(const int& flag,
                 const std::string& nombre,
                 const std::string& archivo_mapa,
                 const int& filas, const int& columnas)
                 : nombre(nombre), filas(filas), columnas(columnas) {
      if (flag == CARGAR_DESDE_ARCHIVO) {
         this->archivo_mapa = archivo_mapa;
         cargarMapaExistente();
      } else {
         if (filas > MAX_FC || columnas > MAX_FC ||
             filas < MIN_FC || columnas < MIN_FC) throw -1;
         this->archivo_mapa = "../common_src/mapas/" + nombre + ".yaml";
      }
    }
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