#include "Editor.h"
#include "dragwidget.h"
#include <QCoreApplication>
#include "MapaEditable.h"



Editor::Editor(QWidget *parent) : QWidget(parent) {
    this->resize(1037, 758);
    std::map<std::string, std::string> mapa_recursos = obtenerMapaRecursos();
    horizontalLayoutWidget = new QWidget(this);
    horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
    horizontalLayoutWidget->setGeometry(QRect(230, 20, 631, 80));
    horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    botonCrearMapa = new QPushButton(horizontalLayoutWidget);
    botonCrearMapa->setText("Crear Mapa");
    botonCrearMapa->setObjectName(QStringLiteral("botonCrearMapa"));

    horizontalLayout->addWidget(botonCrearMapa);

    botonEditarMapa = new QPushButton(horizontalLayoutWidget);
    botonEditarMapa->setObjectName(QStringLiteral("botonEditarMapa"));
    botonEditarMapa->setText("Ediar Mapa");

    horizontalLayout->addWidget(botonEditarMapa);

    verticalLayoutWidget = new DragWidget(this, false);
    verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
    verticalLayoutWidget->setGeometry(QRect(50, 120, 81, 581));
    verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);


    for (auto const& element : mapa_recursos) {
        QLabel* label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromStdString(element.first));
        label->setPixmap(QPixmap(QString::fromStdString(element.second)));
        verticalLayout->addWidget(label);
    }

    gridLayoutWidget = new DragWidget(this, true);
    gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
    gridLayoutWidget->setGeometry(QRect(230, 130, 631, 561));
    gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setHorizontalSpacing(0);
    gridLayout->setVerticalSpacing(0);



    std::string flag;
    flag = QCoreApplication::arguments().at(1).toUtf8().constData();
    std::string map_file;
    map_file = QCoreApplication::arguments().at(2).toUtf8().constData();
    MapaEditable mapa(flag, map_file, 0, 0);
    int n_cols = mapa.getColumnas();
    int n_rows = mapa.getFilas();

    for (int i=0; i < n_rows; i++) {
        for (int k=0; k < n_cols; k++) {
            QLabel* label = new QLabel(gridLayoutWidget);
            std::string pos = "pos_" + std::to_string(i) + "_" + std::to_string(k);
            std::string elemento, imagen;
            mapa.obtenerElemento(pos, elemento);
            imagen = mapa_recursos.at(elemento);
            QString label_name = QString::fromStdString(pos);
            label->setObjectName(label_name);
            label->setStyleSheet("border: 1px solid black;");
            label->setPixmap(QPixmap(QString::fromStdString(imagen)));
            label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            gridLayout->addWidget(label, i, k);
            pos.clear();
            elemento.clear();
        }
    }

    QMetaObject::connectSlotsByName(this);
}

void Editor::crearMapaNuevo() {
}

void Editor::cargarArchivoMapa() {

}

std::map<std::string, std::string> Editor::obtenerMapaRecursos() {
    std::map<std::string, std::string> mapa;
    mapa.insert(std::pair<std::string, std::string>("guardia",
                                                    "../imgs/guard_1.png"));
    mapa.insert(std::pair<std::string, std::string>("ametralladora",
                                                    "../imgs/ametralladora.png"));
    mapa.insert(std::pair<std::string, std::string>("canion_de_fuego",
                                                    "../imgs/canion_de_fuego.png"));
    mapa.insert(std::pair<std::string, std::string>("llave",
                                                    "../imgs/llave.png"));
    mapa.insert(std::pair<std::string, std::string>("medicina",
                                                    "../imgs/medicina.png"));
    mapa.insert(std::pair<std::string, std::string>("trofeo",
                                                    "../imgs/trofeo.png"));
    return mapa;
}

/*
void Editor::conectarEventos() {
    // Conecto el evento del boton
    QPushButton* botonEditarMapa = findChild<QPushButton*>("botonEditarMapa");
    QPushButton* botonCrearMapa = findChild<QPushButton*>("botonCrearMapa");
    QObject::connect(botonEditarMapa, &QPushButton::clicked,
                     this, &Editor::cargarArchivoMapa);
    QObject::connect(botonCrearMapa, &QPushButton::clicked,
                     this, &Editor::crearMapaNuevo);
}
*/
