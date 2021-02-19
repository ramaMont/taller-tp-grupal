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
    createMenu();

    this->setStyleSheet(
    "QWidget {background-image: url(../data/fondo_sangre.jpg) }"
    "QLabel { color : white; }"
    "QMenuBar {color: white;}"
    "QMenu::item {color: white;}"
    "QMessageBox QLabel {color: white;}"
    "QPushButton {color: white;}"
    "QButton {color: white;}"
    "QDialogButton {color: white}"
    "QDialogButtonBox {color: white;}");

    // Obtengo los recursos con los que se crearan los mapas
    gameResources = getResourcesMap();

    // Creo un widget para la creacion del mapa, con su widget y labels.
    createMapWidget = new QWidget(this);
    createMapWidget->setObjectName(QStringLiteral("createMapWidget"));
    createMapWidget->setGeometry(QRect(230, 0, 631, 80));

    rowLabel = new QLabel(this);
    rowLabel->setObjectName("filascolumnsLabel");
    rowLabel->setText("");

    createMapHLayout = new QHBoxLayout(createMapWidget);
    createMapHLayout->setObjectName(QStringLiteral("horizontalLayout"));
    createMapHLayout->setContentsMargins(0, 0, 0, 0);

    createMapHLayout->addWidget(rowLabel);

    // Creo el area donde se dibujará el mapa, tabien con scroll.
    scrollMapArea = new QScrollArea(this);
    scrollMapArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollMapArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollMapArea->setWidgetResizable(true);
    scrollMapArea->setGeometry(QRect(230, 60, 750, 700));

    mapWidget = new MapWidget(this, gameResources);
    mapWidget->setStyleSheet(
        "QWidget {background-image: url(../data/textures/fondo32.png) }");
    scrollMapArea->setWidget(mapWidget);
    scrollMapArea->show();

    // Creo un widget para los recursos con los que armaremos el mapa.
    resourcesWidget = new ResourcesWidget(this, gameResources, mapWidget);
    resourcesWidget->setStyleSheet(
        "QWidget {background-image: url(../data/textures/fondo33.png) }");

    // Agrego una barra de scroll por si los elementos son muchos.
    scrollResourcesArea = new QScrollArea(this);
    scrollResourcesArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollResourcesArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollResourcesArea->setWidgetResizable(true);
    scrollResourcesArea->setGeometry(QRect(50, 60, 95, 700));
    scrollResourcesArea->setWidget(resourcesWidget);
    scrollResourcesArea->show();

    setScrollBarStyle(scrollResourcesArea);
    setScrollBarStyle(scrollMapArea);

    // Conecto eventos
    QMetaObject::connectSlotsByName(this);
    this->show();

    qApp->installEventFilter(this);
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
    " }"));
}

void Editor::createNewMap() {
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

    // Esperar accion del usuario
    if (dialog.exec() == QDialog::Accepted) {
        // Si acepta
        QString nombre_qstring = lineEditNombre->text();
        nombre_qstring.replace(".", "_");
        QString filas_qstring = lineEditFilas->text();
        QString columnas_qstring = lineEditColumnas->text();
        std::string nombre_map = nombre_qstring.toStdString();
        int rows = filas_qstring.toInt();
        int columns = columnas_qstring.toInt();

        // Valido valores.
        if (rows > MAX_RC || columns > MAX_RC ||
            rows < MIN_Rc || columns < MIN_Rc) {
            messageBox = new QMessageBox(this);
            messageBox->setText("El número de rows y columns "
                                "debe estar entre 10 y 40");
            messageBox->setWindowTitle("Error");
            messageBox->setIcon(QMessageBox::Warning);
            messageBox->show();
            return;
        }

        try {
            mapWidget->createNewMap(nombre_map, rows, columns);
        } catch (std::exception& exc) {
            mapWidget->showWarning(QString::fromStdString(exc.what()),
                        QMessageBox::Warning);
            //mapWidget->deleteMap();
            return;
        }
        scrollMapArea->show();
        this->setWindowTitle(nombre_qstring);
        mapWidget->updateLabelRC();
    }
}

bool Editor::showFileDialog() {
    QString file_name = QFileDialog::getOpenFileName(this,
            tr("Editar Mapa"), "",
            tr("Mapas (*.yaml)"));

    std::string map_file = file_name.toUtf8().constData();

    // Limpio el clipboard, el dialog de file lo utiliza.
    QApplication::clipboard()->clear();

    if (!map_file.empty()) {
        // Cargo un nuevo mapa.
        try {
            mapWidget->loadMapFromFile(map_file);
        } catch (std::exception& exc) {
            mapWidget->showWarning(QString::fromStdString(exc.what()),
                        QMessageBox::Warning);
            mapWidget->cleanGridAndMap();
            return false;
        }
        return true;
    }
    return false;
}

void Editor::loadMapFile() {
    if (mapWidget->createdMap()) {
        // Mensaje de confirmación.
        QMessageBox messageBox(QMessageBox::Question, "Alerta",
                                    "El mapa actual se limpiará. "
                                    "Está seguro?",
                                    QMessageBox::Yes|QMessageBox::No,
                                    this);
        messageBox.setButtonText(QMessageBox::Yes, tr("Si"));
        messageBox.setButtonText(QMessageBox::No, tr("No"));

        if (messageBox.exec() == QMessageBox::Yes) {
            if (showFileDialog()) {
                mapWidget->updateWindowName();
                mapWidget->updateLabelRC();
            }
        } else {
            return;
        }
    } else {
        if (showFileDialog()) {
            mapWidget->updateWindowName();
            mapWidget->updateLabelRC();
        }
    }
}

void Editor::saveMap() {
    if (!mapWidget->createdMap()) return;
    mapWidget->saveMap();
}

void Editor::createMenu() {
    auto* new_map = new QAction("&Nuevo Mapa...", this);
    auto* load_map = new QAction("&Cargar Mapa...", this);
    auto* save_map = new QAction("&Guardar", this);

    QMenuBar* menuBar = new QMenuBar(this);
    QMenu *file = menuBar->addMenu("&Archivo");
    file->addAction(new_map);
    file->addAction(load_map);
    file->addAction(save_map);

    connect(new_map, &QAction::triggered, this, &Editor::createNewMap);
    connect(load_map, &QAction::triggered, this, &Editor::loadMapFile);
    connect(save_map, &QAction::triggered, this, &Editor::saveMap);
}

void Editor::keyPressEvent(QKeyEvent* event) {
    // Si capto un ESC, limpio el clipboard y el cursor.
    if (event->key() == Qt::Key_Escape) {
        QApplication::clipboard()->clear();
        QApplication::restoreOverrideCursor();
    } else {QWidget::keyPressEvent(event);}
}


std::map<std::string, std::string> Editor::getResourcesMap() {
    // Genero un mapa con todos los recursos.
    std::map<std::string, std::string> map;

    // Aprovechando que map ordena por las keys, agrego iniciales
    // que caracterizen el tipo de objeto.
    // Armas y jugadores.
    insertInResourcesMap(map, "player_front",
                         "../data/textures/player_front.png");
    insertInResourcesMap(map, "player_left",
                         "../data/textures/player_left.png");
    insertInResourcesMap(map, "player_right",
                         "../data/textures/player_right.png");
    insertInResourcesMap(map, "player_back",
                         "../data/textures/player_back.png");
    insertInResourcesMap(map, "g_machine_gun",
                         "../data/textures/machine_gun.png");
    insertInResourcesMap(map, "g_fire_canon",
                         "../data/textures/fire_canon.png");
    insertInResourcesMap(map, "g_rocket_launcher",
                         "../data/textures/rocket_launcher.png");
    // Pickeables
    insertInResourcesMap(map, "i_key", "../data/textures/key.png");
    insertInResourcesMap(map, "i_medicine", "../data/textures/medicine.png");
    insertInResourcesMap(map, "i_trophie", "../data/textures/trophie.png");
    insertInResourcesMap(map, "i_bullets", "../data/textures/bullets.png");
    insertInResourcesMap(map, "i_food", "../data/textures/food.png");
    // Decoraciones
    insertInResourcesMap(map, "m_water", "../data/textures/water.png");
    insertInResourcesMap(map, "m_barrel", "../data/textures/barrel.png");
    insertInResourcesMap(map, "m_pillar", "../data/textures/pillar_editor.png");
    insertInResourcesMap(map, "m_table", "../data/textures/table.png");
    insertInResourcesMap(map, "m_greenlight",
                         "../data/textures/greenlight_editor.png");

    // Paredes y puertas
    insertInResourcesMap(map, "wall_bluestone",
                         "../data/textures/wall_bluestone_editor.png");
    insertInResourcesMap(map, "wall_greystone",
                         "../data/textures/wall_greystone_editor.png");
    insertInResourcesMap(map, "wall_colorstone",
                         "../data/textures/wall_colorstone_editor.png");
    insertInResourcesMap(map, "wall_redbrick",
                         "../data/textures/wall_redbrick_editor.png");
    insertInResourcesMap(map, "wall_purplestone",
                         "../data/textures/wall_purplestone_editor.png");
    insertInResourcesMap(map, "passage_bluestone",
                         "../data/textures/passage_bluestone.png");
    insertInResourcesMap(map, "passage_colorstone",
                         "../data/textures/passage_colorstone.png");
    insertInResourcesMap(map, "passage_greystone",
                         "../data/textures/passage_greystone.png");
    insertInResourcesMap(map, "passage_purplestone",
                         "../data/textures/passage_purplestone.jpg");
    insertInResourcesMap(map, "passage_redbrick",
                         "../data/textures/passage_redbrick.jpg");
    insertInResourcesMap(map, "v_door",
                         "../data/textures/door_editor.png");
    insertInResourcesMap(map, "v_key_door",
                         "../data/textures/key_door.png");
    return map;
}

void Editor::insertInResourcesMap(std::map<std::string, std::string>& map,
                          std::string key, std::string value) {
    map.insert(std::pair<std::string, std::string>(key, value));
}

bool Editor::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseMove) {
        if (mapWidget->createdMap())
            mapWidget->cleanHighlightedLabel();
    }
    return false;
}

void Editor::closeEvent(QCloseEvent *event) {
    if (mapWidget->createdMap() && !mapWidget->savedMap()){
        // Consulto si desea cerrar y perder cambios.
        QMessageBox::StandardButton answer = QMessageBox::question(
            this,
            tr("Cerrar editor"),
            tr("Está seguro que desea cerrar el editor?"
            "Hay cambios sin guardar y se perderán."),
            QMessageBox::Yes | QMessageBox::No);
        if (answer == QMessageBox::Yes){
            event->accept();
        } else {
            event->ignore();
        }
    } else {
        // Si el mapa ya estaba guardado, cierro
        event->accept();
    }
}
