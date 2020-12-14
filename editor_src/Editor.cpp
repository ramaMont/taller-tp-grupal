#include "Editor.h"
#include <QCoreApplication>
#include <QFileDialog>
#include <QScrollBar>
#include <QAbstractItemView>


Editor::Editor(QWidget *parent) : QWidget(parent) {

    // Tamaño y titulo de la ventana
    this->resize(910, 800);
    this->setWindowTitle(QString("Editor de Mapas - Wolfenstein 3D"));

    // Obtengo los recursos con los que se crearan los mapas
    recursos_del_juego = obtenerMapaRecursos();

    // Creo un widget para el boton de editar mapas.
    widgetEditarMapa = new QWidget(this);
    widgetEditarMapa->setObjectName(QStringLiteral("widgetEditarMapa"));
    widgetEditarMapa->setGeometry(QRect(50, 20, 81, 80));

    horizontalLayoutEditarMapa = new QHBoxLayout(widgetEditarMapa);
    horizontalLayoutEditarMapa->setObjectName(QStringLiteral("horizontalLayoutEditarMapa"));
    horizontalLayoutEditarMapa->setContentsMargins(0, 0, 0, 0);

    botonEditarMapa = new QPushButton(widgetEditarMapa);
    botonEditarMapa->setObjectName(QStringLiteral("botonEditarMapa"));
    botonEditarMapa->setText("Cargar Mapa");

    horizontalLayoutEditarMapa->addWidget(botonEditarMapa);

    // Creo un widget para la creacion del mapa, con su widget y labels.
    widgetCrearMapa = new QWidget(this);
    widgetCrearMapa->setObjectName(QStringLiteral("widgetCrearMapa"));
    widgetCrearMapa->setGeometry(QRect(230, 20, 631, 80));

    nombreLabel = new QLabel(this);
    nombreLabel->setText("Nombre: ");
    filasLabel = new QLabel(this);
    filasLabel->setText("Filas: ");
    columnasLabel = new QLabel(this);
    columnasLabel->setText("Columnas: ");

    horizontalLayoutCrearMapa = new QHBoxLayout(widgetCrearMapa);
    horizontalLayoutCrearMapa->setObjectName(QStringLiteral("horizontalLayout"));
    horizontalLayoutCrearMapa->setContentsMargins(0, 0, 0, 0);

    botonCrearMapa = new QPushButton(widgetCrearMapa);
    botonCrearMapa->setText("Crear Mapa");
    botonCrearMapa->setObjectName(QStringLiteral("botonCrearMapa"));

    inputNombreMapa = new QLineEdit(widgetCrearMapa);
    inputNombreMapa->setObjectName(QStringLiteral("nombreMapa"));
    inputNombreMapa->setClearButtonEnabled(false);

    inputCantidadFilas = new QLineEdit(widgetCrearMapa);
    inputCantidadFilas->setObjectName(QStringLiteral("filas"));
    inputCantidadFilas->setClearButtonEnabled(false);

    inputCantidadColumnas = new QLineEdit(widgetCrearMapa);
    inputCantidadColumnas->setObjectName(QStringLiteral("columnas"));
    inputCantidadColumnas->setClearButtonEnabled(false);

    horizontalLayoutCrearMapa->addWidget(nombreLabel);
    horizontalLayoutCrearMapa->addWidget(inputNombreMapa);
    horizontalLayoutCrearMapa->addWidget(filasLabel);
    horizontalLayoutCrearMapa->addWidget(inputCantidadFilas);
    horizontalLayoutCrearMapa->addWidget(columnasLabel);
    horizontalLayoutCrearMapa->addWidget(inputCantidadColumnas);
    horizontalLayoutCrearMapa->addWidget(botonCrearMapa);

    // Creo un widget para los recursos con los que armaremos el mapa.
    widgetRecursos = new ResourcesWidget(this, recursos_del_juego);

    // Agrego una barra de scroll por si los elementos son muchos.
    scrollResourcesArea = new QScrollArea(this);
    scrollResourcesArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollResourcesArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollResourcesArea->setWidgetResizable(true);
    scrollResourcesArea->setGeometry(QRect(50, 120, 95, 581));
    scrollResourcesArea->setWidget(widgetRecursos);
    scrollResourcesArea->show();

    // Creo el area donde se dibujará el mapa, tabien con scroll.
    scrollMapArea = new QScrollArea(this);
    scrollMapArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollMapArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollMapArea->setWidgetResizable(true);
    scrollMapArea->setGeometry(QRect(230, 120, 631, 581));

    mapWidget = new MapWidget(this, recursos_del_juego);
    scrollMapArea->setWidget(mapWidget);

    widgetMapaGuardar = new QWidget(this);
    widgetMapaGuardar->setObjectName(
        QStringLiteral("widgetCrearMapa"));
    widgetMapaGuardar->setGeometry(QRect(50, 720, 811, 30));

    horizontalLayoutSave = new QHBoxLayout(widgetMapaGuardar);
    horizontalLayoutSave->setObjectName(QStringLiteral("horizontalLayout"));
    horizontalLayoutSave->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    horizontalLayoutSave->setContentsMargins(0, 0, 0, 0);

    botonGuardarMapa = new QPushButton(this);
    botonGuardarMapa->setObjectName(QStringLiteral("botonGuardarMapa"));
    botonGuardarMapa->setText("Guardar");

    const QSize size = QSize(70, 30);
    botonGuardarMapa->setFixedSize(size);
    horizontalLayoutSave->addWidget(botonGuardarMapa,
                                    Qt::AlignCenter | Qt::AlignTop);

    // Conecto eventos
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

    // Valido valores.
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

    mapWidget->crearMapaNuevo(nombre_map, filas, columnas);
    scrollMapArea->show();
}

void Editor::desplegarFileDialog() {
    QString file_name = QFileDialog::getOpenFileName(this,
            tr("Editar Mapa"), "",
            tr("Mapas (*.yaml)"));

    std::string map_file = file_name.toUtf8().constData();

    // Cargo un nuevo mapa.
    mapWidget->cargarMapaDesdeArchivo(map_file);
    mapWidget->cargarLabelsBasicos(inputNombreMapa, inputCantidadFilas,
                                   inputCantidadColumnas);

    // Limpio el clipboard, el dialog de file lo utiliza.
    QApplication::clipboard()->clear();
}

void Editor::cargarArchivoMapa() {
    if (mapWidget->hayMapaCreado()) {
        // Mensaje de confirmación.
        QMessageBox::StandardButton reply;
        QMessageBox messageBox(QMessageBox::Question, "Alerta",
                                    "El mapa actual se limpiará. "
                                    "Está seguro?",
                                    QMessageBox::Yes|QMessageBox::No,
                                    this);
        messageBox.setButtonText(QMessageBox::Yes, tr("Si"));
        messageBox.setButtonText(QMessageBox::No, tr("No"));
        if (messageBox.exec() == QMessageBox::Yes) {
            desplegarFileDialog();
        } else {
            return;
        }
    } else {
        desplegarFileDialog();
    }
}

void Editor::guardarMapa() {
    // TOD: Excepciones.
    if (!mapWidget->hayMapaCreado()) return;
    // Sincronizo el mapa visual con el real y guardo.
    mapWidget->guardarMapa();
    // Mensaje de éxito
    QMessageBox* messageBox = new QMessageBox(this);
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
    // Evento de edicion de mapa
    QObject::connect(botonEditarMapa, &QPushButton::clicked,
                     this, &Editor::cargarArchivoMapa);
    // Evento de creacion de mapa
    QObject::connect(botonCrearMapa, &QPushButton::clicked,
                     this, &Editor::crearMapaNuevo);
    // Evento de guardado de mapa
    QObject::connect(botonGuardarMapa, &QPushButton::clicked,
                     this, &Editor::guardarMapa);
}

void Editor::keyPressEvent(QKeyEvent* event) {
    // Si capto un ESC, limpio el clipboard y el cursor.
    if (event->key() == Qt::Key_Escape) {
        QApplication::clipboard()->clear();
        QApplication::restoreOverrideCursor();
    } else {QWidget::keyPressEvent(event);}
}


std::map<std::string, std::string> Editor::obtenerMapaRecursos() {
    // Genero un mapa con todos los recursos.
    std::map<std::string, std::string> mapa;

    // Armas y jugadores.
    mapa.insert(std::pair<std::string, std::string>("guardia",
                                                    "../imgs/guardia.png"));
    mapa.insert(std::pair<std::string, std::string>("jugador",
                                                    "../imgs/jugador.png"));
    mapa.insert(std::pair<std::string, std::string>("ametralladora",
                                                    "../imgs/ametralladora.png"));
    mapa.insert(std::pair<std::string, std::string>("canion_de_fuego",
                                                    "../imgs/canion_de_fuego.png"));
    mapa.insert(std::pair<std::string, std::string>("lanzacohetes",
                                                    "../imgs/lanzacohetes.png"));
    // Pickeables
    mapa.insert(std::pair<std::string, std::string>("llave",
                                                    "../imgs/llave.png"));
    mapa.insert(std::pair<std::string, std::string>("medicina",
                                                    "../imgs/medicina.png"));
    mapa.insert(std::pair<std::string, std::string>("trofeo",
                                                    "../imgs/trofeo.png"));
    mapa.insert(std::pair<std::string, std::string>("balas",
                                                    "../imgs/balas.png"));
    mapa.insert(std::pair<std::string, std::string>("comida",
                                                    "../imgs/comida.png"));

    // Decoraciones
    mapa.insert(std::pair<std::string, std::string>("agua",
                                                    "../imgs/agua.png"));
    mapa.insert(std::pair<std::string, std::string>("barril",
                                                    "../imgs/barril.png"));

    // Paredes y puertas
    mapa.insert(std::pair<std::string, std::string>("pared",
                                                    "../imgs/pared_1.png"));
    mapa.insert(std::pair<std::string, std::string>("pared_falsa",
                                                    "../imgs/pared_falsa.png"));
    mapa.insert(std::pair<std::string, std::string>("pasadizo_1",
                                                    "../imgs/pasadizo_1.png"));
    mapa.insert(std::pair<std::string, std::string>("pasadizo_2",
                                                    "../imgs/pasadizo_2.png"));
    mapa.insert(std::pair<std::string, std::string>("puerta",
                                                    "../imgs/puerta.png"));
    mapa.insert(std::pair<std::string, std::string>("puerta_con_llave",
                                                    "../imgs/puerta_con_llave.png"));

    return mapa;
}