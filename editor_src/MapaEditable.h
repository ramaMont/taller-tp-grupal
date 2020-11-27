#include <iostream>
#include <string>
#include <map>
#include <fstream>

#define FILAS 20
#define COLUMNAS 20

class MapaEditable {
 public:
    MapaEditable(const std::string& flag,
                 const std::string& archivo_mapa,
                 const int& filas, const int& columnas)
                 : archivo_mapa(archivo_mapa), filas(filas),
                 columnas(columnas) {
      if (filas > FILAS || columnas > COLUMNAS) throw -1;
      if (flag == "--crear") {
         iniciarNuevoMapa(filas, columnas);
      }
      if (flag == "--editar") {
         cargarMapaExistente();
      }
    }
    void iniciarNuevoMapa(const int& rows, const int& columns);
    void cargarMapaExistente();
    void cargarElemento(const std::string& posicion,
                        const std::string& elemento);
    void obtenerElemento(const std::string& posicion,
                         std::string& elemento);
    void guardarMapa();
    int getColumnas();
    int getFilas();

 private:
    std::map<std::string, std::string> mapa;
    std::string archivo_mapa;
    std::string nombre;
    int filas;
    int columnas;
};
