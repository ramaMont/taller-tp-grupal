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
#include "ResourcesWidget.h"
#include "MapWidget.h"

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
    QScrollArea *scrollMapArea;
    QScrollArea *scrollResourcesArea;
    QLabel* nombreLabel;
    QLabel* filasLabel;
    QLabel* columnasLabel;
    QLineEdit *inputNombreMapa;
    QLineEdit *inputCantidadFilas;
    QLineEdit *inputCantidadColumnas;
    MapWidget *mapWidget;
    QPushButton *botonSonido;
    std::map<std::string, std::string> recursos_del_juego;
    void crearMapaNuevo();
    void cargarArchivoMapa();
    void conectarEventos();
    void guardarMapa();
    void keyPressEvent(QKeyEvent* event) override;
    void desplegarFileDialog();
    void setScrollBarStyle(QScrollArea* scrollArea);
    std::map<std::string, std::string> obtenerMapaRecursos();
};

#endif // GREETER_H
