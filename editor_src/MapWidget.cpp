#include "MapWidget.h"
#include <iostream>
#include <QObject>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QApplication>
#include <sstream>
#include <string>


MapWidget::MapWidget(QWidget *parent,
                     const std::map<std::string, std::string>& mapa_recursos)
    : QFrame(parent), mapa_recursos(mapa_recursos) {
    mapa_creado = false;
    this->setObjectName(QStringLiteral("mapWidget"));
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setHorizontalSpacing(0);
    gridLayout->setVerticalSpacing(0);
    this->setLayout(gridLayout);
    setAcceptDrops(true);
}

bool MapWidget::hayMapaCreado() {
    return mapa_creado;
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

void MapWidget::intercambiarLabels(const std::string& pos_1,
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
    if (label_elemento_2->text().toStdString() != "vacio") {
        QPixmap image_2 = label_visual_2->pixmap()->copy();
        label_visual_1->setPixmap(image_2);
    } else {
        label_visual_1->setPixmap(QPixmap());
    }
    if (label_elemento_1->text().toStdString() != "vacio") {
        QPixmap image_1 = label_visual_1->pixmap()->copy();
        label_visual_2->setPixmap(image_1);
    } else {
        label_visual_2->setPixmap(QPixmap());
    }
    label_elemento_2->setText(element_1);
    label_elemento_1->setText(element_2);
}

void MapWidget::crearCeldaVacia(const std::string& pos,
                                const int& fila,
                                const int& columna) {
    // Genero el label visual y el elemento vacio.
    QLabel* label = new QLabel(this);
    QLabel* hidden_label = new QLabel(this);
    hidden_label->setVisible(false);
    QString label_name = QString::fromStdString(pos);
    label->setObjectName(label_name);
    hidden_label->setObjectName(label_name + "_element");
    hidden_label->setText("vacio");
    label->setFixedWidth(MIN_WIDTH_SIZE);
    label->setFixedHeight(MIN_HEIGHT_SIZE);
    label->setStyleSheet("border: 0.5px ridge grey;");
    // Agrego al layout.
    gridLayout->addWidget(label, fila, columna);
    gridLayout->addWidget(hidden_label);
    mapa->cargarElemento(pos, "vacio");
}

void MapWidget::agregarColumnaAPartirDe(int columna) {
    int nueva_columna = mapa->getColumnas();
    // Agrego una nueva columna con vacios
    for (int i=0; i < mapa->getFilas(); i++) {
        std::string pos = "pos_" + std::to_string(i)
            + "_" + std::to_string(nueva_columna);
        crearCeldaVacia(pos, i, nueva_columna);
    }
    // Intercambio el contenido de los labels hasta llegar al actual.
    for (int i=nueva_columna; i > columna; i--) {
        for (int k=0; k < mapa->getFilas(); k++) {
            std::string pos_1 = "pos_" + std::to_string(k)
                + "_" + std::to_string(i);
            std::string pos_2 = "pos_" + std::to_string(k)
                + "_" + std::to_string(i-1);
            intercambiarLabels(pos_1, pos_2);
        }
    }
    mapa->agregarColumna();
}

void MapWidget::agregarFilaAPartirDe(int fila) {
    int nueva_fila = mapa->getFilas();
    // Agrego una nueva fila con vacios
    for (int i=0; i < mapa->getColumnas(); i++) {
        std::string pos = "pos_" + std::to_string(nueva_fila)
            + "_" + std::to_string(i);
        crearCeldaVacia(pos, nueva_fila, i);
    }
    // Intercambio el contenido de los labels hasta llegar al actual.
    for (int i=nueva_fila; i > fila; i--) {
        for (int k=0; k < mapa->getColumnas(); k++) {
            std::string pos_1 = "pos_" + std::to_string(i)
                + "_" + std::to_string(k);
            std::string pos_2 = "pos_" + std::to_string(i-1)
                + "_" + std::to_string(k);
            intercambiarLabels(pos_1, pos_2);
        }
    }
    mapa->agregarFila();
}

void MapWidget::desplegarMenuOpciones(QMouseEvent *event, QLabel* label_visual,
                                      QLabel* label_elemento) {
    QMenu contextMenu;
    std::string current_pos = label_visual->objectName().toStdString();
    std::istringstream ss(current_pos);
    std::string token;
    std::getline(ss, token, '_');
    std::getline(ss, token, '_');
    int fila = std::stoi(token);
    std::getline(ss, token, '_');
    int columna = std::stoi(token);
    contextMenu.addAction("Insertar columna a la izquierda", this, [=] {
        agregarColumnaAPartirDe(columna);
    });
    contextMenu.addAction("Insertar columna a la derecha", this, [=] {
        agregarColumnaAPartirDe(columna+1);
    });
    contextMenu.addAction("Insertar fila arriba", this, [=] {
        agregarFilaAPartirDe(fila);
    });
    contextMenu.addAction("Insertar fila abajo", this, [=] {
        agregarFilaAPartirDe(fila+1);
    });
    contextMenu.addAction("Eliminar fila", this, [=] {
        std::cout << "ABJ" << std::endl;
    });
    contextMenu.addAction("Eliminar columna", this, [=] {
        std::cout << "ABJ" << std::endl;
    });
    QPoint globalPos = mapToGlobal(event->pos());
    contextMenu.exec(globalPos);
}

void MapWidget::pointAndClick(QLabel* label_visual, QLabel* label_elemento) {
    QByteArray itemData = QApplication::clipboard()->mimeData()
                            ->data("application/x-dnditemdata");
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);
    QPixmap pixmap;
    QPoint offset;
    dataStream >> pixmap >> offset;
    pixmap.scaled(180, 180, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    label_visual->setPixmap(pixmap);
    label_elemento->setText(QApplication::clipboard()->mimeData()->text());
}

void MapWidget::ejecutarDrag(QMouseEvent *event, QLabel* label_visual,
                             QLabel* label_elemento) {
    // Si es un elemento vacio, no tiene sentido drag & drop a partir de este.
    if (label_elemento->text().toStdString() == "vacio") return;

    const QPixmap* pixmap = label_visual->pixmap();

    // Leo lo clickeado
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << *pixmap << QPoint(event->pos() - label_visual->pos());

    // Preparo la data a mover en el drag
    QMimeData *mimeData = new QMimeData;
    QString text = label_elemento->text();
    mimeData->setData("application/x-dnditemdata", itemData);
    mimeData->setText(text);

    // Preparo el drag
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(*pixmap);
    drag->setHotSpot(event->pos() - label_visual->pos());

    // Ejecuto el drag, y al terminar, limpio el correspondiente.
    drag->exec(Qt::CopyAction | Qt::MoveAction,
            Qt::CopyAction);
    label_visual->setPixmap(QPixmap());
    label_elemento->setText("vacio");
}

void MapWidget::mousePressEvent(QMouseEvent *event) {
    // Obtengo el label grafico, y el oculto que tiene el elemento.
    QLabel* label_visual = static_cast<QLabel*>(childAt(event->pos()));
    QLabel* label_elemento = findChild<QLabel*>
                                (label_visual->objectName() + "_element");
    if (!label_visual)
        return;

    // Si es click derecho, despliego el menu de opciones
    if (event->button() == Qt::RightButton) {
        desplegarMenuOpciones(event, label_visual, label_elemento);
        return;
    } else {
        // Si es click izquierdo, se intentara mover elementos.
        if (QApplication::clipboard()->mimeData()->hasText()) {
            // Si habia algo en el clipboard, quiere decir que este click
            // tiene como objetivo pintar, y no hacer el drag & drop.
            pointAndClick(label_visual, label_elemento);
            return;
        }
        // iniciar drag & drop
        ejecutarDrag(event, label_visual, label_elemento);
    }
}

void MapWidget::fabricarMapa(const int& flag) {
    int filas = mapa->getFilas();
    int columnas = mapa->getColumnas();

    for (int i=0; i < filas; i++) {
        for (int k=0; k < columnas; k++) {
            // Creo un label visual, que guarda la imagen del recurso
            // y un label oculto, que guarda el nombre del elemento.
            QLabel* label = new QLabel(this);
            QLabel* hidden_label = new QLabel(this);
            hidden_label->setVisible(false);
            std::string pos = "pos_" + std::to_string(i)
                + "_" + std::to_string(k);
            QString label_name = QString::fromStdString(pos);
            label->setObjectName(label_name);
            hidden_label->setObjectName(label_name + "_element");
            if (flag == CARGAR_DESDE_ARCHIVO) {
                // Si se carga un mapa existente, obtengo el elemento y dibujo
                std::string elemento, imagen;
                mapa->obtenerElemento(pos, elemento);
                if (elemento != "vacio") {
                    imagen = mapa_recursos.at(elemento);
                    hidden_label->setText(QString::fromStdString(elemento));
                    label->setPixmap(QPixmap(QString::fromStdString(imagen)));
                } else {
                    hidden_label->setText(QString::fromStdString("vacio"));
                }
                elemento.clear();
            } else {
                mapa->cargarElemento(pos, "vacio");
                hidden_label->setText(QString::fromStdString("vacio"));
            }
            label->setFixedWidth(MIN_WIDTH_SIZE);
            label->setFixedHeight(MIN_HEIGHT_SIZE);
            label->setStyleSheet("border: 0.5px ridge grey;");
            label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            gridLayout->addWidget(label, i, k);
            gridLayout->addWidget(hidden_label);
            pos.clear();
        }
    }
    mapa_creado = true;
}

void MapWidget::crearMapaNuevo(const std::string& nombre,
                               const int& filas, const int& columnas) {
    limpiarGridYMapa();
    mapa = new MapaEditable(NUEVO_MAPA, nombre, "", filas, columnas);
    fabricarMapa(NUEVO_MAPA);
}

void MapWidget::cargarMapaDesdeArchivo(const std::string& map_file) {
    limpiarGridYMapa();
    mapa = new MapaEditable(CARGAR_DESDE_ARCHIVO, "", map_file, 0, 0);
    fabricarMapa(CARGAR_DESDE_ARCHIVO);
}

void MapWidget::cargarLabelsBasicos(QLineEdit* nombre_mapa,
                                    QLineEdit* cantidad_filas,
                                    QLineEdit* cantidad_columnas) {
    nombre_mapa->setText(QString::fromStdString(mapa->getNombre()));
    cantidad_filas->setText(QString::number(mapa->getFilas()));
    cantidad_columnas->setText(QString::number(mapa->getColumnas()));
}

void MapWidget::guardarMapa() {
    sincronizarMapaYVista();
    mapa->guardarMapa();
}

void MapWidget::sincronizarMapaYVista() {
    // Recorro el mapa y en base al contenido de la grafica, actualizo.
    for (int i = 0; i < gridLayout->count(); i++) {
        QLabel* label = static_cast<QLabel*> (gridLayout->itemAt(i)->widget());
        if (label->objectName().endsWith("_element")) continue;
        QLabel* hidden_label = findChild<QLabel*>(label->objectName()
                               + "_element");
        mapa->actualizarElemento(label->objectName().toStdString(),
                                 hidden_label->text().toStdString());
    }
}

void MapWidget::limpiarGridYMapa() {
    if (mapa_creado) {
        delete mapa;
        QGridLayout* gridLayout = findChild<QGridLayout*>("gridLayout");
        for (int i = 0; i < gridLayout->count(); i++) {
            gridLayout->itemAt(i)->widget()->deleteLater();
        }
    }
}