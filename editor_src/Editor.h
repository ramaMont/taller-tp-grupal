#ifndef GREETER_H
#define GREETER_H

#include <string>
#include <iostream>
#include <QApplication>
#include <QMouseEvent>
#include <QtWidgets>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMimeData>
#include <QPainter>
#include <QDrag>
#include <map>
#include <QGridLayout>
#include <QStandardItemModel>
#include <QVariant>
#include <QScrollArea>
#include <QMessageBox>
#include "MapaEditable.h"

#define MIN_WIDTH_SIZE 80
#define MIN_HEIGHT_SIZE 80


class Editor : public QWidget {
public:
    explicit Editor(QWidget *parent = 0);

private:
    // Creo los widgets asignandole un padre
    QMessageBox* messageBox;
    QWidget *widgetEditarMapa;
    QHBoxLayout *horizontalLayoutCrearMapa;
    QHBoxLayout *horizontalLayoutSave;
    QHBoxLayout *horizontalLayoutEditarMapa;
    QPushButton *botonCrearMapa;
    QPushButton *botonEditarMapa;
    QPushButton* botonGuardarMapa;
    QWidget *widgetCrearMapa;
    QWidget *widgetMapaGuardar;
    QWidget *widgetRecursos;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollMapArea;
    QScrollArea *scrollResourcesArea;
    QLabel* nombreLabel;
    QLabel* filasLabel;
    QLabel* columnasLabel;
    QLineEdit *inputNombreMapa;
    QLineEdit *inputCantidadFilas;
    QLineEdit *inputCantidadColumnas;
    QWidget *mapWidget;
    QGridLayout *gridLayout;
    QPushButton *botonSonido;
    bool mapa_creado;
    MapaEditable* mapa;
    std::map<std::string, std::string> mapa_recursos;
    void crearMapaNuevo();
    void cargarArchivoMapa();
    void conectarEventos();
    void fabricarMapa(const int& flag);
    void limpiarGrid();
    void guardarMapa();
    void sincronizarMapaYVista();
    void keyPressEvent(QKeyEvent* event) override;
    void desplegarFileDialog();
    std::map<std::string, std::string> obtenerMapaRecursos();
};

#endif // GREETER_H
