#include <QFrame>
#include <QtWidgets>
#include <Qt>
#include <QContextMenuEvent>
#include <string>
#include <QGridLayout>
#include <QMessageBox>
#include <QMainWindow>
#include <iostream>
#include <map>
#include "MapaEditable.h"

#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#define MIN_WIDTH_SIZE 80
#define MIN_HEIGHT_SIZE 80
#define MESSAGEBOX_TYPE_INFO 0
#define MESSAGEBOX_TYPE_ALERT 1

class MapWidget : public QFrame
{
 public:
    explicit MapWidget(QWidget *parent,
                       const std::map<std::string, std::string>& mapa_recursos);
    bool hayMapaCreado();
    void fabricarMapa(const int& flag);
    void guardarMapa();
    void crearMapaNuevo(const std::string& nombre,
                        const int& filas, const int& columnas);
    void cargarMapaDesdeArchivo(const std::string& map_file);
    void actualizarNombreVentana();
    void actualizarLabelFyC();
    void pintarParedes(QString object_name);

 protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

 private:
    MapaEditable* mapa;
    QGridLayout* gridLayout;
    std::map<std::string, std::string> mapa_recursos;
    QLabel* highlighted_label;
    bool mapa_creado;
    void limpiarGridYMapa();
    void pointAndClick(QLabel* label_visual, QLabel* label_elemento);
    void desplegarMenuOpciones(QMouseEvent *event, QLabel* label_visual,
                               QLabel* label_elemento);
    void ejecutarDrag(QMouseEvent *event, QLabel* label_visual,
                      QLabel* label_elemento);
    void sincronizarMapaYVista();
    void agregarColumnaAPartirDe(int columna);
    void agregarFilaAPartirDe(int fila);
    void eliminarFila(int fila);
    void eliminarColumna(int fila);
    void mostrarWarning(QString message, QMessageBox::Icon icon);
    bool validarParedes();
    bool validarPuertas();
    void intercambiarLabels(const std::string& pos_1,
                            const std::string& pos_2);
    void crearCeldaVacia(const std::string& pos, const int& fila,
                         const int& columna);
};

#endif  // MAPWIDGET_H