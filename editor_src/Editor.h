#ifndef GREETER_H
#define GREETER_H

#include <string>
#include <iostream>
#include <QApplication>
#include <QMouseEvent>

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMimeData>
#include <QPainter>
#include <QDrag>
#include <map>
#include <QTableView>
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
    QWidget *horizontalLayoutWidget;
    QMessageBox* messageBox;
    QWidget *horizontalLayoutWidget2;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayoutSave;
    QHBoxLayout *horizontalLayout2;
    QPushButton *botonCrearMapa;
    QPushButton *botonEditarMapa;
    QPushButton* botonGuardarMapa;
    QWidget *horizontalLayoutWidgetSave;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QLabel* nombreLabel;
    QLabel* filasLabel;
    QLabel* columnasLabel;
    QLineEdit *inputNombreMapa;
    QLineEdit *inputCantidadFilas;
    QLineEdit *inputCantidadColumnas;
    QLabel *guard_1;
    QLabel *guard_2;
    QLabel *guard_3;
    QLabel *guard_4;
    QLabel *guard_5;
    QLabel *guard_6;
    QWidget *mapWidget;
    QGridLayout *gridLayout;
    QLabel *label_2_3;
    QLabel *label_2_1;
    QLabel *label_1_1;
    QLabel *label_1_2;
    QLabel *label_1_3;
    QLabel *label_2_2;
    QLabel *label_3_1;
    QLabel *label_3_2;
    QLabel *label_3_3;
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
    std::map<std::string, std::string> obtenerMapaRecursos();
};

#endif // GREETER_H
