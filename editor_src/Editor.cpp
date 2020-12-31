#include "Editor.h"
#include <QCoreApplication>
#include <QFileDialog>
#include <QScrollBar>
#include <QDialog>
#include <QMenuBar>
#include <QList>
#include <QFormLayout>
#include <QAbstractItemView>


Editor::Editor(QWidget *parent) : QWidget(parent) {

    // Tamaño y titulo de la ventana
    this->resize(1050, 800);
    this->setWindowTitle(QString("Editor de Mapas - Wolfenstein 3D"));
    fabricarMenu();

    this->setStyleSheet("QWidget {background-image: url(imgs/fondo3.png) }"
    "QLabel { color : white; }"
    "QMenuBar {color: white;}"
    "QMenu::item {color: white;}"
    "QMessageBox QLabel {color: white;}"
    "QPushButton {color: white;}"
    "QButton {color: white;}"
    "QDialogButton {color: white}"
    "QDialogButtonBox {color: white;}");

    // Obtengo los recursos con los que se crearan los mapas
    recursos_del_juego = obtenerMapaRecursos();

    // Creo un widget para la creacion del mapa, con su widget y labels.
    widgetCrearMapa = new QWidget(this);
    widgetCrearMapa->setObjectName(QStringLiteral("widgetCrearMapa"));
    widgetCrearMapa->setGeometry(QRect(230, 0, 631, 80));

    filasLabel = new QLabel(this);
    filasLabel->setObjectName("filasColumnasLabel");
    filasLabel->setText("");

    horizontalLayoutCrearMapa = new QHBoxLayout(widgetCrearMapa);
    horizontalLayoutCrearMapa->setObjectName(QStringLiteral("horizontalLayout"));
    horizontalLayoutCrearMapa->setContentsMargins(0, 0, 0, 0);

    horizontalLayoutCrearMapa->addWidget(filasLabel);

    // Creo el area donde se dibujará el mapa, tabien con scroll.
    scrollMapArea = new QScrollArea(this);
    scrollMapArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollMapArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollMapArea->setWidgetResizable(true);
    scrollMapArea->setGeometry(QRect(230, 60, 750, 700));

    mapWidget = new MapWidget(this, recursos_del_juego);
    mapWidget->setStyleSheet("QWidget {background-image: url(imgs/fondo32.png) }");
    scrollMapArea->setWidget(mapWidget);
    scrollMapArea->show();

    // Creo un widget para los recursos con los que armaremos el mapa.
    widgetRecursos = new ResourcesWidget(this, recursos_del_juego, mapWidget);
    widgetRecursos->setStyleSheet("QWidget {background-image: url(imgs/fondo33.png) }");

    // Agrego una barra de scroll por si los elementos son muchos.
    scrollResourcesArea = new QScrollArea(this);
    scrollResourcesArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollResourcesArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollResourcesArea->setWidgetResizable(true);
    scrollResourcesArea->setGeometry(QRect(50, 60, 95, 700));
    scrollResourcesArea->setWidget(widgetRecursos);
    scrollResourcesArea->show();

    setScrollBarStyle(scrollResourcesArea);
    setScrollBarStyle(scrollMapArea);

    // Conecto eventos
    QMetaObject::connectSlotsByName(this);
    this->show();
}

void Editor::setScrollBarStyle(QScrollArea* scrollArea) {
    scrollArea->setStyleSheet(QString::fromUtf8(
    "QScrollBar:horizontal {"
    "    border: 2px solid grey;"
    "    background: #32CC99;"
    "    height: 15px;"
    "    margin: 0px 20px 0 20px;"
    "}"
    "QScrollBar::handle:horizontal {"
    "    background: white;"
    "    min-width: 20px;"
    "}"
    "QScrollBar::add-line:horizontal {"
    "    border: 2px solid grey;"
    "    background: #32CC99;"
    "    width: 20px;"
    "    subcontrol-position: right;"
    "    subcontrol-origin: margin;"
    "}"
    ""
    "QScrollBar::sub-line:horizontal {"
    "    border: 2px solid grey;"
    "    background: #32CC99;"
    "    width: 20px;"
    "    subcontrol-position: left;"
    "    subcontrol-origin: margin;"
    "}"
    "QScrollBar::left-arrow:horizontal, QScrollBar::right-arrow:horizontal {"
    "     border: 2px solid grey;"
    "     width: 3px;"
    "     height: 3px;"
    "     background: white;"
    " }"
    ""
    " QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {"
    "     background: none;"
    " }"
    "QScrollBar:vertical {"
    "     border: 2px solid grey;"
    "     background: #32CC99;"
    "     width: 15px;"
    "     margin: 22px 0 22px 0;"
    " }"
    " QScrollBar::handle:vertical {"
    "     background: white;"
    "     min-height: 20px;"
    " }"
    " QScrollBar::add-line:vertical {"
    "     border: 2px solid grey;"
    "     background: #32CC99;"
    "     height: 20px;"
    "     subcontrol-position: bottom;"
    "     subcontrol-origin: margin;"
    " }"
    ""
    " QScrollBar::sub-line:vertical {"
    "     border: 2px solid grey;"
    "     background: #32CC99;"
    "     height: 20px;"
    "     subcontrol-position: top;"
    "     subcontrol-origin: margin;"
    " }"
    " QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
    "     border: 2px solid grey;"
    "     width: 3px;"
    "     height: 3px;"
    "     background: white;"
    " }"
    ""
    " QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
    "     background: none;"
    " }"
    ));
}

void Editor::crearMapaNuevo() {
    QDialog dialog(this);
    dialog.setWindowTitle(QString("Nuevo mapa"));
    // Creo un dialog con un form
    QFormLayout form(&dialog);

    // Agrego una lista con los campos
    QList<QLineEdit *> fields;

    // Nombre del mapa
    QLineEdit* lineEditNombre = new QLineEdit(&dialog);
    QString labelNombre = QString("Nombre");
    form.addRow(labelNombre, lineEditNombre);
    fields << lineEditNombre;

    // Filas
    QLineEdit* lineEditFilas = new QLineEdit(&dialog);
    QString labelFilas = QString("Filas");
    form.addRow(labelFilas, lineEditFilas);
    fields << lineEditFilas;

    // Nombre del mapa
    QLineEdit* lineEditColumnas = new QLineEdit(&dialog);
    QString labelColumnas = QString("Columnas");
    form.addRow(labelColumnas, lineEditColumnas);
    fields << lineEditColumnas;

    // Botones
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                            Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    // Conecto eventos
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        QString nombre_qstring = lineEditNombre->text();
        QString filas_qstring = lineEditFilas->text();
        QString columnas_qstring = lineEditColumnas->text();
        std::string nombre_map = nombre_qstring.toStdString();
        int filas = filas_qstring.toInt();
        int columnas = columnas_qstring.toInt();

        // Valido valores.
        if (filas > MAX_FC || columnas > MAX_FC ||
            filas < MIN_FC || columnas < MIN_FC) {
            messageBox = new QMessageBox(this);
            messageBox->setText("El número de filas y columnas "
                                "debe estar entre 10 y 50");
            messageBox->setWindowTitle("Error");
            messageBox->setIcon(QMessageBox::Warning);
            messageBox->show();
            return;
        }

        mapWidget->crearMapaNuevo(nombre_map, filas, columnas);
        scrollMapArea->show();
        this->setWindowTitle(nombre_qstring);
        mapWidget->actualizarLabelFyC();
    }
}

void Editor::desplegarFileDialog() {
    QString file_name = QFileDialog::getOpenFileName(this,
            tr("Editar Mapa"), "",
            tr("Mapas (*.yaml)"));

    std::string map_file = file_name.toUtf8().constData();

    // Cargo un nuevo mapa.
    mapWidget->cargarMapaDesdeArchivo(map_file);

    // Limpio el clipboard, el dialog de file lo utiliza.
    QApplication::clipboard()->clear();
}

void Editor::cargarArchivoMapa() {
    if (mapWidget->hayMapaCreado()) {
        // Mensaje de confirmación.
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
        mapWidget->actualizarNombreVentana();
        mapWidget->actualizarLabelFyC();
    }
}

void Editor::guardarMapa() {
    // TOD: Excepciones.
    if (!mapWidget->hayMapaCreado()) return;
    // Sincronizo el mapa visual con el real y guardo.
    mapWidget->guardarMapa();
}

void Editor::fabricarMenu() {
    auto* nuevo_mapa = new QAction("&Nuevo Mapa...", this);
    auto* cargar_mapa = new QAction("&Cargar Mapa...", this);
    auto* guardar_mapa = new QAction("&Guardar", this);

    QMenuBar* menuBar = new QMenuBar(this);
    QMenu *file = menuBar->addMenu("&Archivo");
    file->addAction(nuevo_mapa);
    file->addAction(cargar_mapa);
    file->addAction(guardar_mapa);

    connect(nuevo_mapa, &QAction::triggered, this, &Editor::crearMapaNuevo);
    connect(cargar_mapa, &QAction::triggered, this, &Editor::cargarArchivoMapa);
    connect(guardar_mapa, &QAction::triggered, this, &Editor::guardarMapa);
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
                                                    "imgs/guardia.png"));
    mapa.insert(std::pair<std::string, std::string>("jugador",
                                                    "imgs/jugador.png"));
    mapa.insert(std::pair<std::string, std::string>("ametralladora",
                                                    "imgs/ametralladora.png"));
    mapa.insert(std::pair<std::string, std::string>("canion_de_fuego",
                                                    "imgs/canion_de_fuego.png"));
    mapa.insert(std::pair<std::string, std::string>("lanzacohetes",
                                                    "imgs/lanzacohetes.png"));
    // Pickeables
    mapa.insert(std::pair<std::string, std::string>("llave",
                                                    "imgs/llave.png"));
    mapa.insert(std::pair<std::string, std::string>("medicina",
                                                    "imgs/medicina.png"));
    mapa.insert(std::pair<std::string, std::string>("trofeo",
                                                    "imgs/trofeo.png"));
    mapa.insert(std::pair<std::string, std::string>("balas",
                                                    "imgs/balas.png"));
    mapa.insert(std::pair<std::string, std::string>("comida",
                                                    "imgs/comida.png"));

    // Decoraciones
    mapa.insert(std::pair<std::string, std::string>("agua",
                                                    "imgs/agua.png"));
    mapa.insert(std::pair<std::string, std::string>("barril",
                                                    "imgs/barril.png"));

    // Paredes y puertas
    mapa.insert(std::pair<std::string, std::string>("pared",
                                                    "imgs/pared_1.png"));
    mapa.insert(std::pair<std::string, std::string>("pared_1",
                                                    "imgs/pared_2.png"));
    mapa.insert(std::pair<std::string, std::string>("pared_2",
                                                    "imgs/pared_3.png"));
    mapa.insert(std::pair<std::string, std::string>("pared_3",
                                                    "imgs/pared_4.png"));
    mapa.insert(std::pair<std::string, std::string>("pasadizo",
                                                    "imgs/pasadizo.png"));
    mapa.insert(std::pair<std::string, std::string>("puerta",
                                                    "imgs/puerta.png"));
    mapa.insert(std::pair<std::string, std::string>("puerta_con_llave",
                                                    "imgs/puerta_con_llave.png"));

    return mapa;
}