#include "Editor.h"
#include "dragwidget.h"
#include <QCoreApplication>
#include <QFileDialog>
#include <QScrollBar>
#include <QAbstractItemView>


Editor::Editor(QWidget *parent) : QWidget(parent) {
    this->resize(1037, 800);

    mapa_recursos = obtenerMapaRecursos();

    horizontalLayoutWidget2 = new QWidget(this);
    horizontalLayoutWidget2->setObjectName(QStringLiteral("horizontalLayoutWidget"));
    horizontalLayoutWidget2->setGeometry(QRect(50, 20, 81, 80));

    horizontalLayout2 = new QHBoxLayout(horizontalLayoutWidget2);
    horizontalLayout2->setObjectName(QStringLiteral("horizontalLayout"));
    horizontalLayout2->setContentsMargins(0, 0, 0, 0);

    horizontalLayoutWidget = new QWidget(this);
    horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
    horizontalLayoutWidget->setGeometry(QRect(230, 20, 631, 80));

    nombreLabel = new QLabel(tr("Nombre:"));
    filasLabel = new QLabel(tr("Filas:"));
    columnasLabel = new QLabel(tr("Columnas:"));

    horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    botonCrearMapa = new QPushButton(horizontalLayoutWidget);
    botonCrearMapa->setText("Crear Mapa");
    botonCrearMapa->setObjectName(QStringLiteral("botonCrearMapa"));

    botonEditarMapa = new QPushButton(horizontalLayoutWidget);
    botonEditarMapa->setObjectName(QStringLiteral("botonEditarMapa"));
    botonEditarMapa->setText("Cargar Mapa");

    inputNombreMapa = new QLineEdit(horizontalLayoutWidget);
    inputNombreMapa->setObjectName(QStringLiteral("nombreMapa"));
    inputNombreMapa->setClearButtonEnabled(false);

    inputCantidadFilas = new QLineEdit(horizontalLayoutWidget);
    inputCantidadFilas->setObjectName(QStringLiteral("filas"));
    inputCantidadFilas->setClearButtonEnabled(false);

    inputCantidadColumnas = new QLineEdit(horizontalLayoutWidget);
    inputCantidadColumnas->setObjectName(QStringLiteral("columnas"));
    inputCantidadColumnas->setClearButtonEnabled(false);

    horizontalLayout2->addWidget(botonEditarMapa);
    horizontalLayout->addWidget(nombreLabel);
    horizontalLayout->addWidget(inputNombreMapa);
    horizontalLayout->addWidget(filasLabel);
    horizontalLayout->addWidget(inputCantidadFilas);
    horizontalLayout->addWidget(columnasLabel);
    horizontalLayout->addWidget(inputCantidadColumnas);
    horizontalLayout->addWidget(botonCrearMapa);

    mapa_creado = false;

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

    scrollArea = new QScrollArea(this);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setWidgetResizable(true);
    scrollArea->setGeometry(QRect(230, 130, 631, 561));

    mapWidget = new DragWidget();
    mapWidget->setObjectName(QStringLiteral("mapWidget"));
    mapWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setWidget(mapWidget);

    gridLayout = new QGridLayout();
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setHorizontalSpacing(0);
    gridLayout->setVerticalSpacing(0);
    mapWidget->setLayout(gridLayout);

    horizontalLayoutWidgetSave = new QWidget(this);
    horizontalLayoutWidgetSave->setObjectName(
        QStringLiteral("horizontalLayoutWidget"));
    horizontalLayoutWidgetSave->setGeometry(QRect(230, 400, 631, 650));

    horizontalLayoutSave = new QHBoxLayout(horizontalLayoutWidgetSave);
    horizontalLayoutSave->setObjectName(QStringLiteral("horizontalLayout"));
    horizontalLayoutSave->setContentsMargins(0, 0, 0, 0);

    botonGuardarMapa = new QPushButton(horizontalLayoutWidgetSave);
    botonGuardarMapa->setObjectName(QStringLiteral("botonGuardarMapa"));
    botonGuardarMapa->setText("Guardar");

    const QSize size = QSize(70, 30);
    botonGuardarMapa->setFixedSize(size);
    horizontalLayoutSave->addWidget(botonGuardarMapa, Qt::AlignCenter);

    QMetaObject::connectSlotsByName(this);
    conectarEventos();
    this->show();
}

void Editor::crearMapaNuevo() {
    QLineEdit* nombre_mapa = findChild<QLineEdit*>("nombreMapa");
    QString nombre = nombre_mapa->text();

    QLineEdit* cantidad_filas = findChild<QLineEdit*>("filas");
    QString filas_str = cantidad_filas->text();
    int filas = filas_str.toInt();

    QLineEdit* cantidad_columnas = findChild<QLineEdit*>("columnas");
    QString columnas_str = cantidad_columnas->text();
    int columnas = columnas_str.toInt();

    if (filas > MAX_FC || columnas > MAX_FC ||
        filas < MIN_FC || columnas < MIN_FC) {
        messageBox = new QMessageBox(this);
        messageBox->setText("El número de filas y columnas "
                            "debe estar entre 8 y 50");
        messageBox->setWindowTitle("Error");
        messageBox->setIcon(QMessageBox::Warning);
        messageBox->show();
        return;
    }

    std::string nombre_map = nombre.toStdString();

    limpiarGrid();
    mapa = new MapaEditable(NUEVO_MAPA, nombre_map,
                            "", filas, columnas);

    fabricarMapa(NUEVO_MAPA);
}

void Editor::fabricarMapa(const int& flag) {
    int filas = mapa->getFilas();
    int columnas = mapa->getColumnas();

    for (int i=0; i < filas; i++) {
        for (int k=0; k < columnas; k++) {
            QLabel* label = new QLabel(mapWidget);
            std::string pos = "pos_" + std::to_string(i)
                + "_" + std::to_string(k);
            if (flag == CARGAR_DESDE_ARCHIVO) {
                std::string elemento, imagen;
                mapa->obtenerElemento(pos, elemento);
                if (elemento != "vacio") {
                    imagen = mapa_recursos.at(elemento);
                    label->setPixmap(QPixmap(QString::fromStdString(imagen)));
                }
                elemento.clear();
            } else {
                mapa->cargarElemento(pos, "vacio");
            }
            QString label_name = QString::fromStdString(pos);
            label->setFixedWidth(MIN_WIDTH_SIZE);
            label->setFixedHeight(MIN_HEIGHT_SIZE);
            label->setObjectName(label_name);
            label->setStyleSheet("border: 1px solid black;");
            label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            gridLayout->addWidget(label, i, k);
            pos.clear();
        }
    }
    scrollArea->show();
    mapa_creado = true;
}

void Editor::cargarArchivoMapa() {
    QString file_name = QFileDialog::getOpenFileName(this,
        tr("Editar Mapa"), "",
        tr("Mapas (*.yaml)"));

    std::string map_file = file_name.toUtf8().constData();

    limpiarGrid();
    mapa = new MapaEditable(CARGAR_DESDE_ARCHIVO, "", map_file, 0, 0);

    QLineEdit* nombre_mapa = findChild<QLineEdit*>("nombreMapa");
    nombre_mapa->setText(QString::fromStdString(mapa->getNombre()));

    QLineEdit* cantidad_filas = findChild<QLineEdit*>("filas");
    cantidad_filas->setText(QString::number(mapa->getFilas()));

    QLineEdit* cantidad_columnas = findChild<QLineEdit*>("columnas");
    cantidad_columnas->setText(QString::number(mapa->getColumnas()));

    fabricarMapa(CARGAR_DESDE_ARCHIVO);
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

void Editor::limpiarGrid() {
    if (mapa_creado) {
        delete mapa;
        QGridLayout* gridLayout = findChild<QGridLayout*>("gridLayout");
        for (int i = 0; i < gridLayout->count(); i++) {
            gridLayout->itemAt(i)->widget()->deleteLater();
        }
    }
}


void Editor::guardarMapa() {
    mapa->guardarMapa();
    messageBox = new QMessageBox(this);
    messageBox->setText("Mapa guardado con exito!");
    messageBox->setWindowTitle("Aviso");
    messageBox->setIcon(QMessageBox::Information);
    messageBox->show();
}

void Editor::conectarEventos() {
    // Conecto el evento del boton
    QPushButton* botonEditarMapa = findChild<QPushButton*>("botonEditarMapa");
    QPushButton* botonCrearMapa = findChild<QPushButton*>("botonCrearMapa");
    QPushButton* botonGuardarMapa = findChild<QPushButton*>("botonGuardarMapa");
    QObject::connect(botonEditarMapa, &QPushButton::clicked,
                     this, &Editor::cargarArchivoMapa);
    QObject::connect(botonCrearMapa, &QPushButton::clicked,
                     this, &Editor::crearMapaNuevo);
    QObject::connect(botonGuardarMapa, &QPushButton::clicked,
                     this, &Editor::guardarMapa);
}

