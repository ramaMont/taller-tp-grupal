#include "MapWidget.h"
#include <iostream>
#include <QObject>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QApplication>
#include <sstream>
#include <string>


MapWidget::MapWidget(QWidget *parent,
                     const std::map<std::string, std::string>& resourcesMap)
    : QFrame(parent), resourcesMap(resourcesMap) {
    mapCreated = false;
    this->setObjectName(QStringLiteral("mapWidget"));
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setHorizontalSpacing(0);
    gridLayout->setVerticalSpacing(0);
    highlightedLabel = nullptr;
    this->setLayout(gridLayout);
    setAcceptDrops(true);
    map = nullptr;
}

bool MapWidget::createdMap() {
    return mapCreated;
}

void MapWidget::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void MapWidget::dragMoveEvent(QDragMoveEvent *event) {
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            QPoint pt = this->mapFromGlobal(QCursor::pos());
            QWidget* child = childAt(pt);
            QLabel* child_label = qobject_cast<QLabel *>(child);
            if (child_label == originLabel) return;
            if (highlightedLabel != nullptr) {
                highlightedLabel->setStyleSheet("QWidget:hover{background-color:#D9FAC5;}");
            }
            highlightedLabel = child_label;
            highlightedLabel->setStyleSheet("QWidget { background-color : #D9FAC5; }");
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}


void MapWidget::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        // Leo la data del evento.
        QByteArray itemData = event->mimeData()
                                   ->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        // Busco el label en el que se realizó el drop.
        QPoint pt = this->mapFromGlobal(QCursor::pos());
        QWidget* child = childAt(pt);
        if (child) {
            // Si lo encontre, lo casteo y traigo el label hidden asociado.
            QLabel* label = qobject_cast<QLabel *>(child);
            QLabel* hidden_label = findChild<QLabel*>
                                   (label->objectName() + "_element");
            pixmap.scaled(180, 180, Qt::IgnoreAspectRatio,
                          Qt::FastTransformation);
            label->setPixmap(pixmap);
            hidden_label->setText(event->mimeData()->text());
        }

        if (highlightedLabel != nullptr) {
            highlightedLabel->setStyleSheet("QWidget:hover{background-color:#D9FAC5;}");
        }

        if (event->source() == this) {
            // Envio una señal de movimiento para el fin del drag.
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void MapWidget::swapLabels(const std::string& pos_1,
                                   const std::string& pos_2) {
    // Traigo los labels.
    QLabel* label_visual_1 = findChild<QLabel*> (QString::fromStdString(pos_1));
    QLabel* label_elemento_1 = findChild<QLabel*>
        (QString::fromStdString(pos_1) + "_element");
    QLabel* label_visual_2 = findChild<QLabel*> (QString::fromStdString(pos_2));
    QLabel* label_elemento_2 = findChild<QLabel*>
        (QString::fromStdString(pos_2) + "_element");
    // Tomo sus elementos, y los intercambio.
    QString element_1 = label_elemento_1->text();
    QString element_2 = label_elemento_2->text();

    QPixmap image_1;
    QPixmap image_2;

    if (element_1.toStdString() != "empty") {
        image_1 = label_visual_1->pixmap()->copy();
    } else {
        image_1 = QPixmap();
    }

    if (element_2.toStdString() != "empty") {
        image_2 = label_visual_2->pixmap()->copy();
    } else {
        image_2 = QPixmap();
    }

    label_visual_1->setPixmap(image_2);
    label_visual_2->setPixmap(image_1);
    label_elemento_2->setText(element_1);
    label_elemento_1->setText(element_2);
}

void MapWidget::createEmptyCell(const std::string& pos,
                                const int& row,
                                const int& column) {
    // Genero el label visual y el element empty.
    QLabel* label = new QLabel(this);
    QLabel* hidden_label = new QLabel(this);
    hidden_label->setVisible(false);
    QString label_name = QString::fromStdString(pos);
    label->setObjectName(label_name);
    hidden_label->setObjectName(label_name + "_element");
    hidden_label->setText("empty");
    label->setFixedWidth(MIN_WIDTH_SIZE);
    label->setFixedHeight(MIN_HEIGHT_SIZE);
    label->setStyleSheet("QWidget:hover{background-color:#D9FAC5;}");
    // Agrego al layout.
    gridLayout->addWidget(label, row, column);
    gridLayout->addWidget(hidden_label);
    map->loadElement(pos, "empty");
}

void MapWidget::updateLabelRC() {
    // Busco el label correspondiente a rows y columns.
    QLabel* fyc = parent()->parent()->parent()
                    ->findChild<QLabel*> ("filascolumnsLabel");
    int rows = map->getRows();
    int columns = map->getColumns();
    std::string text = "Filas: " + std::to_string(rows)
        + "   Columnas: " + std::to_string(columns);
    fyc->setText(QString::fromStdString(text));
}

void MapWidget::addCoumnFrom(int column) {
    int nueva_columna = map->getColumns();
    if (nueva_columna >= MAX_RC) {
        std::string message = "El máximo de columns es de "
            + std::to_string(MAX_RC);
        showWarning(QString::fromStdString(message), QMessageBox::Warning);
        return;
    }
    // Agrego una nueva column con emptys
    for (int i=0; i < map->getRows(); i++) {
        std::string pos = "pos_" + std::to_string(i)
            + "_" + std::to_string(nueva_columna);
        createEmptyCell(pos, i, nueva_columna);
    }
    // Intercambio el contenido de los labels hasta llegar al actual.
    for (int i=nueva_columna; i > column; i--) {
        for (int k=0; k < map->getRows(); k++) {
            std::string pos_1 = "pos_" + std::to_string(k)
                + "_" + std::to_string(i);
            std::string pos_2 = "pos_" + std::to_string(k)
                + "_" + std::to_string(i-1);
            swapLabels(pos_1, pos_2);
        }
    }
    map->addColumn();
    updateLabelRC();
}

void MapWidget::addRowFrom(int row) {
    int nueva_fila = map->getRows();
    if (nueva_fila >= MAX_RC) {
        std::string message = "El máximo de rows es de "
            + std::to_string(MAX_RC);
        showWarning(QString::fromStdString(message), QMessageBox::Warning);
        return;
    }
    // Agrego una nueva row con emptys
    for (int i=0; i < map->getColumns(); i++) {
        std::string pos = "pos_" + std::to_string(nueva_fila)
            + "_" + std::to_string(i);
        createEmptyCell(pos, nueva_fila, i);
    }
    // Intercambio el contenido de los labels hasta llegar al actual.
    for (int i=nueva_fila; i > row; i--) {
        for (int k=0; k < map->getColumns(); k++) {
            std::string pos_1 = "pos_" + std::to_string(i)
                + "_" + std::to_string(k);
            std::string pos_2 = "pos_" + std::to_string(i-1)
                + "_" + std::to_string(k);
            swapLabels(pos_1, pos_2);
        }
    }
    map->addRow();
    updateLabelRC();
}

void MapWidget::deleteRow(int row) {
    int ultima_fila = map->getRows()-1;
    if (ultima_fila < MIN_Rc) {
        std::string message = "El minimo de rows es de "
            + std::to_string(MIN_Rc);
        showWarning(QString::fromStdString(message), QMessageBox::Warning);
        return;
    }

    // Intercambio el contenido de los labels hasta llegar al actual.
    for (int i=row; i <= ultima_fila; i++) {
        for (int k=0; k < map->getColumns(); k++) {
            std::string pos_1 = "pos_" + std::to_string(i)
                + "_" + std::to_string(k);
            std::string pos_2 = "pos_" + std::to_string(i-1)
                + "_" + std::to_string(k);
            swapLabels(pos_1, pos_2);
        }
    }
    // Elimino todos los elementos de la ultima row
    for (int i=0; i < map->getColumns(); i++) {
        std::string pos = "pos_" + std::to_string(ultima_fila)
            + "_" + std::to_string(i);
        QLabel* visual_label = findChild<QLabel*> (QString::fromStdString(pos));
        QLabel* element_label = findChild<QLabel*>
            (QString::fromStdString(pos) + "_element");
        visual_label->deleteLater();
        element_label->deleteLater();
    }

    map->deleteRow();
    updateLabelRC();
}

void MapWidget::deleteColumn(int column) {
    // Elimino todos los elementos de la celda
    int ultima_columna = map->getColumns()-1;
    if (ultima_columna < MIN_Rc) {
        std::string message = "El minimo de columns es de "
            + std::to_string(MIN_Rc);
        showWarning(QString::fromStdString(message), QMessageBox::Warning);
        return;
    }

    // Intercambio el contenido de los labels hasta llegar al ultimo.
    for (int i=column; i <= ultima_columna; i++) {
        for (int k=0; k < map->getRows(); k++) {
            std::string pos_1 = "pos_" + std::to_string(k)
                + "_" + std::to_string(i);
            std::string pos_2 = "pos_" + std::to_string(k)
                + "_" + std::to_string(i-1);
            swapLabels(pos_1, pos_2);
        }
    }
    // Elimino todos los elementos de la ultima column
    for (int i=0; i < map->getRows(); i++) {
        std::string pos = "pos_" + std::to_string(i)
            + "_" + std::to_string(ultima_columna);
        QLabel* visual_label = findChild<QLabel*> (QString::fromStdString(pos));
        QLabel* element_label = findChild<QLabel*>
            (QString::fromStdString(pos) + "_element");
        visual_label->deleteLater();
        element_label->deleteLater();
    }

    map->deleteColumn();
    updateLabelRC();
}

void MapWidget::showOptionsMenu(QMouseEvent *event, QLabel* visual_label,
                                      QLabel* element_label) {
    QMenu contextMenu;
    std::string current_pos = visual_label->objectName().toStdString();
    std::istringstream ss(current_pos);
    std::string token;
    std::getline(ss, token, '_');
    std::getline(ss, token, '_');
    int row = std::stoi(token);
    std::getline(ss, token, '_');
    int column = std::stoi(token);
    contextMenu.addAction("Insertar column a la izquierda", this, [=] {
        addCoumnFrom(column);
    });
    contextMenu.addAction("Insertar column a la derecha", this, [=] {
        addCoumnFrom(column+1);
    });
    contextMenu.addAction("Insertar row arriba", this, [=] {
        addRowFrom(row);
    });
    contextMenu.addAction("Insertar row abajo", this, [=] {
        addRowFrom(row+1);
    });
    contextMenu.addAction("Eliminar row", this, [=] {
        deleteRow(row+1);
    });
    contextMenu.addAction("Eliminar column", this, [=] {
        deleteColumn(column+1);
    });
    QPoint globalPos = mapToGlobal(event->pos());
    contextMenu.exec(globalPos);

    if (highlightedLabel != nullptr) {
        highlightedLabel->setStyleSheet("QWidget:hover{background-color:#D9FAC5;}");
    }
}

void MapWidget::pointAndClick(QLabel* visual_label, QLabel* element_label) {
    QByteArray itemData = QApplication::clipboard()->mimeData()
                            ->data("application/x-dnditemdata");
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);
    QPixmap pixmap;
    QPoint offset;
    dataStream >> pixmap >> offset;
    pixmap.scaled(180, 180, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    visual_label->setPixmap(pixmap);
    element_label->setText(QApplication::clipboard()->mimeData()->text());
}

void MapWidget::executeDrag(QMouseEvent *event, QLabel* visual_label,
                             QLabel* element_label) {
    // Si es un element empty, no tiene sentido drag & drop a partir de este.
    if (element_label->text().toStdString() == "empty") return;

    const QPixmap* pixmap = visual_label->pixmap();

    // Leo lo clickeado
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << *pixmap << QPoint(event->pos() - visual_label->pos());

    // Preparo la data a mover en el drag
    QMimeData *mimeData = new QMimeData;
    QString text = element_label->text();
    mimeData->setData("application/x-dnditemdata", itemData);
    mimeData->setText(text);

    // Preparo el drag
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(*pixmap);
    drag->setHotSpot(event->pos() - visual_label->pos());

    // Ejecuto el drag, y al terminar, limpio el correspondiente.
    drag->exec(Qt::CopyAction | Qt::MoveAction,
            Qt::CopyAction);
    visual_label->setPixmap(QPixmap());
    element_label->setText("empty");
}

void MapWidget::mousePressEvent(QMouseEvent *event) {
    if (!createdMap()) return;
    // Obtengo el label grafico, y el oculto que tiene el element.
    QLabel* visual_label = static_cast<QLabel*>(childAt(event->pos()));
    QLabel* element_label = findChild<QLabel*>
                                (visual_label->objectName() + "_element");
    if (!visual_label)
        return;

    highlightedLabel = visual_label;
    originLabel = visual_label;

    // Si es click derecho, despliego el menu de opciones
    if (event->button() == Qt::RightButton) {
        showOptionsMenu(event, visual_label, element_label);
        return;
    } else {
        // Si es click izquierdo, se intentara mover elementos.
        if (QApplication::clipboard()->mimeData()->hasText()) {
            // Si habia algo en el clipboard, quiere decir que este click
            // tiene como objetivo pintar, y no hacer el drag & drop.
            pointAndClick(visual_label, element_label);
            return;
        }
        // iniciar drag & drop
        executeDrag(event, visual_label, element_label);
    }
}

void MapWidget::constructMap(const int& flag) {
    int rows = map->getRows();
    int columns = map->getColumns();

    for (int i=0; i < rows; i++) {
        for (int k=0; k < columns; k++) {
            // Creo un label visual, que guarda la imagen del recurso
            // y un label oculto, que guarda el name del element.
            bool error = false;
            QLabel* label = new QLabel(this);
            QLabel* hidden_label = new QLabel(this);
            hidden_label->setVisible(false);
            std::string pos = "pos_" + std::to_string(i)
                + "_" + std::to_string(k);
            QString label_name = QString::fromStdString(pos);
            label->setObjectName(label_name);
            hidden_label->setObjectName(label_name + "_element");
            if (flag == LOAD_FROM_FILE) {
                // Si se carga un mapa existente, obtengo el element y dibujo
                std::string element, imagen;
                map->getElement(pos, element);
                if (element != "empty") {
                    try {
                        imagen = resourcesMap.at(element);
                    } catch(...) {
                        error = true;
                        showWarning("Elemento desconocido detectado!"
                            " El mismo se reemplazará por vacio",
                            QMessageBox::Warning);
                    }
                    if (!error) {
                        hidden_label->setText(QString::fromStdString(element));
                        label->setPixmap(QPixmap(QString::fromStdString(imagen)));
                    } else {
                        hidden_label->setText(QString::fromStdString("empty"));
                    }
                } else {
                    hidden_label->setText(QString::fromStdString("empty"));
                }
                element.clear();
            } else {
                map->loadElement(pos, "empty");
                hidden_label->setText(QString::fromStdString("empty"));
            }
            label->setFixedWidth(MIN_WIDTH_SIZE);
            label->setFixedHeight(MIN_HEIGHT_SIZE);
            label->setStyleSheet("QWidget:hover{background-color:#D9FAC5;}");
            label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            gridLayout->addWidget(label, i, k);
            gridLayout->addWidget(hidden_label);
            pos.clear();
        }
    }
    mapCreated = true;
}

void MapWidget::createNewMap(const std::string& name,
                               const int& rows, const int& columns) {
    cleanGridAndMap();
    map = new EditableMap(NEW_MAP, name, "", rows, columns);
    constructMap(NEW_MAP);
}

void MapWidget::loadMapFromFile(const std::string& map_file) {
    cleanGridAndMap();
    map = new EditableMap(LOAD_FROM_FILE, "", map_file, 0, 0);
    constructMap(LOAD_FROM_FILE);
}

void MapWidget::updateWindowName() {
    QWidget* window = static_cast<QWidget*> (this->parent()->parent()->parent());
    window->setWindowTitle(QString::fromStdString(map->getName()));
}

void MapWidget::saveMap() {
    synchronizeMapAndView();
    try {
        map->validateMap();
    } catch (MapException& exc) {
        showWarning(QString::fromStdString(exc.what()),
                       QMessageBox::Warning);
        return;
    }
    map->saveMap();
    std::string message = "Mapa guardado con éxito!";
    showWarning(QString::fromStdString(message), QMessageBox::Information);
}

void MapWidget::synchronizeMapAndView() {
    map->clean();
    // Recorro el mapa y en base al contenido de la grafica, actualizo.
    for (int i = 0; i < gridLayout->count(); i++) {
        QLabel* label = static_cast<QLabel*> (gridLayout->itemAt(i)->widget());
        if (label->objectName().endsWith("_element")) continue;
        QLabel* hidden_label = findChild<QLabel*>(label->objectName()
                               + "_element");
        map->updateElement(label->objectName().toStdString(),
                                 hidden_label->text().toStdString());
    }
}

void MapWidget::cleanGridAndMap() {
    if (mapCreated) {
        delete map;
        QGridLayout* gridLayout = findChild<QGridLayout*>("gridLayout");
        for (int i = 0; i < gridLayout->count(); i++) {
            gridLayout->itemAt(i)->widget()->deleteLater();
        }
        mapCreated = false;
        highlightedLabel = nullptr;
    }
}

void MapWidget::showWarning(QString message, QMessageBox::Icon icon) {
    QMessageBox messageBox(this);
    messageBox.setStyleSheet(
        "QWidget {background-image: url(imgs/fondo3.png) }"
    "QLabel { color : white; }"
    "QMenuBar {color: white;}"
    "QMenu::item {color: white;}"
    "QMessageBox QLabel {color: white;}"
    "QPushButton {color: white;}"
    "QButton {color: white;}"
    "QDialogButton {color: white}"
    "QDialogButtonBox {color: white;}");
    messageBox.setText(message);
    messageBox.setWindowTitle("Aviso");
    messageBox.setIcon(icon);
    messageBox.exec();
}

void MapWidget::paintWalls(QString object_name) {
    std::string imagen = resourcesMap.at(object_name.toStdString());
    int rows = map->getRows();
    int columns = map->getColumns();
    for (int c=0; c < columns; c++) {
        std::string pos_primera_fila = "pos_0_" + std::to_string(c);
        std::string pos_ultima_fila = "pos_" + std::to_string(rows-1)
            + "_" + std::to_string(c);
        QLabel* label_primera_fila = findChild<QLabel*>(QString::fromStdString(pos_primera_fila));
        QLabel* label_ultima_fila = findChild<QLabel*>(QString::fromStdString(pos_ultima_fila));
        QLabel* label_primera_fila_e = findChild<QLabel*>(QString::fromStdString(pos_primera_fila + "_element"));
        QLabel* label_ultima_fila_e = findChild<QLabel*>(QString::fromStdString(pos_ultima_fila + "_element"));
        label_primera_fila->setPixmap(QPixmap(QString::fromStdString(imagen)));
        label_primera_fila_e->setText(object_name);
        label_ultima_fila->setPixmap(QPixmap(QString::fromStdString(imagen)));
        label_ultima_fila_e->setText(object_name);
    }

    for (int f=0; f < rows; f++) {
        std::string pos_primera_columna = "pos_" + std::to_string(f) + "_0";
        std::string pos_ultima_columna = "pos_" + std::to_string(f)
            + "_" + std::to_string(columns-1);
        QLabel* label_primera_fila = findChild<QLabel*>(QString::fromStdString(pos_primera_columna));
        QLabel* label_ultima_fila = findChild<QLabel*>(QString::fromStdString(pos_ultima_columna));
        QLabel* label_primera_fila_e = findChild<QLabel*>(QString::fromStdString(pos_primera_columna + "_element"));
        QLabel* label_ultima_fila_e = findChild<QLabel*>(QString::fromStdString(pos_ultima_columna + "_element"));
        label_primera_fila->setPixmap(QPixmap(QString::fromStdString(imagen)));
        label_primera_fila_e->setText(object_name);
        label_ultima_fila->setPixmap(QPixmap(QString::fromStdString(imagen)));
        label_ultima_fila_e->setText(object_name);
    }
}

void MapWidget::cleanHighlightedLabel() {
    if (highlightedLabel != nullptr) {
        highlightedLabel->setStyleSheet("QWidget { background-color : transparent; }");
        highlightedLabel->setStyleSheet("QWidget:hover{background-color:#D9FAC5;}");
    }
}


MapWidget::~MapWidget() {
    if (createdMap())
        delete map;
}