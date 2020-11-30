#include <iostream>
#include <string>
#include <map>
#include <fstream>

#define MAX_FC 50
#define MIN_FC 8
#define CARGAR_DESDE_ARCHIVO 1
#define NUEVO_MAPA 0

class MapaEditable {
 public:
    MapaEditable(const int& flag,
                 const std::string& nombre,
                 const std::string& archivo_mapa,
                 const int& filas, const int& columnas)
                 : archivo_mapa(archivo_mapa), filas(filas),
                 nombre(nombre), columnas(columnas) {
      if (flag == CARGAR_DESDE_ARCHIVO) {
         cargarMapaExistente();
      } else {
         if (filas > MAX_FC || columnas > MAX_FC ||
             filas < MIN_FC || columnas < MIN_FC) throw -1;
      }
    }
    ~MapaEditable();
    void iniciarNuevoMapa(const int& rows, const int& columns);
    void cargarMapaExistente();
    void cargarElemento(const std::string& posicion,
                        const std::string& elemento);
    void obtenerElemento(const std::string& posicion,
                         std::string& elemento);
    void guardarMapa();
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
