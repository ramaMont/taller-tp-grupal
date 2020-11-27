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

class Editor : public QWidget {
public:
    explicit Editor(QWidget *parent = 0);
private:
    // Creo los widgets asignandole un padre
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *botonCrearMapa;
    QPushButton *botonEditarMapa;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *guard_1;
    QLabel *guard_2;
    QLabel *guard_3;
    QLabel *guard_4;
    QLabel *guard_5;
    QLabel *guard_6;
    QWidget *gridLayoutWidget;
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
    void crearMapaNuevo();
    void cargarArchivoMapa();
    //void conectarEventos();
    std::map<std::string, std::string> obtenerMapaRecursos();
};

#endif // GREETER_H
