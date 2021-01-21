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
    highlighted_label = nullptr;
    this->setLayout(gridLayout);
    setAcceptDrops(true);
    mapa = nullptr;
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
            QPoint pt = this->mapFromGlobal(QCursor::pos());
            QWidget* child = childAt(pt);
            if (highlighted_label != nullptr)
                highlighted_label->setStyleSheet("QWidget:hover{background-color:#D9FAC5;}");
            highlighted_label = qobject_cast<QLabel *>(child);
            highlighted_label->setStyleSheet("QLabel { background-color : #D9FAC5; }");
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

        highlighted_label->setStyleSheet("QWidget:hover{background-color:#D9FAC5;}");

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

void MapWidget::crearCeldaVacia(const std::string& pos,
                                const int& fila,
                                const int& columna) {
    // Genero el label visual y el elemento empty.
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
    gridLayout->addWidget(label, fila, columna);
    gridLayout->addWidget(hidden_label);
    mapa->cargarElemento(pos, "empty");
}

void MapWidget::actualizarLabelFyC() {
    // Busco el label correspondiente a filas y columnas.
    QLabel* fyc = parent()->parent()->parent()
                    ->findChild<QLabel*> ("filasColumnasLabel");
    int filas = mapa->getFilas();
    int columnas = mapa->getColumnas();
    std::string text = "Filas: " + std::to_string(filas)
        + "   Columnas: " + std::to_string(columnas);
    fyc->setText(QString::fromStdString(text));
}

void MapWidget::agregarColumnaAPartirDe(int columna) {
    int nueva_columna = mapa->getColumnas();
    if (nueva_columna >= MAX_FC) {
        std::string message = "El máximo de columnas es de "
            + std::to_string(MAX_FC);
        mostrarWarning(QString::fromStdString(message), QMessageBox::Warning);
        return;
    }
    // Agrego una nueva columna con emptys
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
    actualizarLabelFyC();
}

void MapWidget::agregarFilaAPartirDe(int fila) {
    int nueva_fila = mapa->getFilas();
    if (nueva_fila >= MAX_FC) {
        std::string message = "El máximo de filas es de "
            + std::to_string(MAX_FC);
        mostrarWarning(QString::fromStdString(message), QMessageBox::Warning);
        return;
    }
    // Agrego una nueva fila con emptys
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
    actualizarLabelFyC();
}

void MapWidget::eliminarFila(int fila) {
    int ultima_fila = mapa->getFilas()-1;
    if (ultima_fila < MIN_FC) {
        std::string message = "El minimo de filas es de "
            + std::to_string(MIN_FC);
        mostrarWarning(QString::fromStdString(message), QMessageBox::Warning);
        return;
    }

    // Intercambio el contenido de los labels hasta llegar al actual.
    for (int i=fila; i <= ultima_fila; i++) {
        for (int k=0; k < mapa->getColumnas(); k++) {
            std::string pos_1 = "pos_" + std::to_string(i)
                + "_" + std::to_string(k);
            std::string pos_2 = "pos_" + std::to_string(i-1)
                + "_" + std::to_string(k);
            intercambiarLabels(pos_1, pos_2);
        }
    }
    // Elimino todos los elementos de la ultima fila
    for (int i=0; i < mapa->getColumnas(); i++) {
        std::string pos = "pos_" + std::to_string(ultima_fila)
            + "_" + std::to_string(i);
        QLabel* label_visual = findChild<QLabel*> (QString::fromStdString(pos));
        QLabel* label_elemento = findChild<QLabel*>
            (QString::fromStdString(pos) + "_element");
        label_visual->deleteLater();
        label_elemento->deleteLater();
    }

    mapa->eliminarFila();
    actualizarLabelFyC();
}

void MapWidget::eliminarColumna(int columna) {
    // Elimino todos los elementos de la celda
    int ultima_columna = mapa->getColumnas()-1;
    if (ultima_columna < MIN_FC) {
        std::string message = "El minimo de columnas es de "
            + std::to_string(MIN_FC);
        mostrarWarning(QString::fromStdString(message), QMessageBox::Warning);
        return;
    }

    // Intercambio el contenido de los labels hasta llegar al ultimo.
    for (int i=columna; i <= ultima_columna; i++) {
        for (int k=0; k < mapa->getFilas(); k++) {
            std::string pos_1 = "pos_" + std::to_string(k)
                + "_" + std::to_string(i);
            std::string pos_2 = "pos_" + std::to_string(k)
                + "_" + std::to_string(i-1);
            intercambiarLabels(pos_1, pos_2);
        }
    }
    // Elimino todos los elementos de la ultima columna
    for (int i=0; i < mapa->getFilas(); i++) {
        std::string pos = "pos_" + std::to_string(i)
            + "_" + std::to_string(ultima_columna);
        QLabel* label_visual = findChild<QLabel*> (QString::fromStdString(pos));
        QLabel* label_elemento = findChild<QLabel*>
            (QString::fromStdString(pos) + "_element");
        label_visual->deleteLater();
        label_elemento->deleteLater();
    }

    mapa->eliminarColumna();
    actualizarLabelFyC();
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
        eliminarFila(fila+1);
    });
    contextMenu.addAction("Eliminar columna", this, [=] {
        eliminarColumna(columna+1);
    });
    QPoint globalPos = mapToGlobal(event->pos());
    contextMenu.exec(globalPos);

    if (highlighted_label != nullptr)
        highlighted_label->setStyleSheet("QWidget:hover{background-color:#D9FAC5;}");
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
    // Si es un elemento empty, no tiene sentido drag & drop a partir de este.
    if (label_elemento->text().toStdString() == "empty") return;

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
    label_elemento->setText("empty");
}

void MapWidget::mousePressEvent(QMouseEvent *event) {
    if (!hayMapaCreado()) return;
    // Obtengo el label grafico, y el oculto que tiene el elemento.
    QLabel* label_visual = static_cast<QLabel*>(childAt(event->pos()));
    QLabel* label_elemento = findChild<QLabel*>
                                (label_visual->objectName() + "_element");
    highlighted_label = label_visual;
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
                if (elemento != "empty") {
                    imagen = mapa_recursos.at(elemento);
                    hidden_label->setText(QString::fromStdString(elemento));
                    label->setPixmap(QPixmap(QString::fromStdString(imagen)));
                } else {
                    hidden_label->setText(QString::fromStdString("empty"));
                }
                elemento.clear();
            } else {
                mapa->cargarElemento(pos, "empty");
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

void MapWidget::actualizarNombreVentana() {
    QWidget* window = static_cast<QWidget*> (this->parent()->parent()->parent());
    window->setWindowTitle(QString::fromStdString(mapa->getNombre()));
}

void MapWidget::guardarMapa() {
    sincronizarMapaYVista();
    if (!validarParedes()) return;
    if (!validarPuertas()) return;

    mapa->guardarMapa();
    std::string message = "Mapa guardado con éxito!";
    mostrarWarning(QString::fromStdString(message), QMessageBox::Information);
}

bool MapWidget::validarPuertas() {

    int filas = mapa->getFilas();
    int columnas = mapa->getColumnas();

    for (int i=1; i < filas-1; i++) {
        for (int k=1; k < columnas-1; k++) {
            std::string pos = "pos_" + std::to_string(i) + "_" + std::to_string(k);
            QLabel* label = findChild<QLabel*>(QString::fromStdString(pos + "_element"));
            if (label->text().startsWith("door")) {
                std::string fila_previa = "pos_" + std::to_string(i-1) + "_" + std::to_string(k);
                std::string fila_siguiente = "pos_" + std::to_string(i+1) + "_" + std::to_string(k);
                std::string columna_previa = "pos_" + std::to_string(i) + "_" + std::to_string(k-1);
                std::string columna_siguiente = "pos_" + std::to_string(i) + "_" + std::to_string(k+1);
                QLabel* label_fprevia = findChild<QLabel*>(QString::fromStdString(fila_previa + "_element"));
                QLabel* label_fsig = findChild<QLabel*>(QString::fromStdString(fila_siguiente + "_element"));
                QLabel* label_cprevia = findChild<QLabel*>(QString::fromStdString(columna_previa + "_element"));
                QLabel* label_csig = findChild<QLabel*>(QString::fromStdString(columna_siguiente + "_element"));
                if (!(label_fprevia->text().startsWith("wall") & label_fsig->text().startsWith("wall")) & 
                    !(label_cprevia->text().startsWith("wall") & label_csig->text().startsWith("wall"))) {
                    std::string message = "Las puertas deben estar rodeadas de paredes!";
                    mostrarWarning(QString::fromStdString(message), QMessageBox::Warning);
                    return false;
                }
            }
        }
    }
    return true;
}

bool MapWidget::validarParedes() {
    // Validar que todos los bordes sean paredes.
    // TODO: Se podria usar excepciones
    int filas = mapa->getFilas();
    int columnas = mapa->getColumnas();
    for (int c=0; c < columnas; c++) {
        std::string pos_primera_fila = "pos_0_" + std::to_string(c);
        std::string pos_ultima_fila = "pos_" + std::to_string(filas-1)
            + "_" + std::to_string(c);
        QLabel* label_primera_fila_e = findChild<QLabel*>(QString::fromStdString(pos_primera_fila + "_element"));
        QLabel* label_ultima_fila_e = findChild<QLabel*>(QString::fromStdString(pos_ultima_fila + "_element"));
        if ((!label_primera_fila_e->text().startsWith("wall")) ||
            (!label_ultima_fila_e->text().startsWith("wall"))) {
            std::string message = "Los bordes del mapa deben ser paredes!";
            mostrarWarning(QString::fromStdString(message), QMessageBox::Warning);
            return false;
        }
    }

    for (int f=0; f < filas; f++) {
        std::string pos_primera_columna = "pos_" + std::to_string(f) + "_0";
        std::string pos_ultima_columna = "pos_" + std::to_string(f)
            + "_" + std::to_string(columnas-1);
        QLabel* label_primera_columna_e = findChild<QLabel*>(QString::fromStdString(pos_primera_columna + "_element"));
        QLabel* label_ultima_columna_e = findChild<QLabel*>(QString::fromStdString(pos_ultima_columna + "_element"));
        if ((!label_primera_columna_e->text().startsWith("wall")) ||
            (!label_ultima_columna_e->text().startsWith("wall"))) {
            std::string message = "Los bordes del mapa deben ser paredes!";
            mostrarWarning(QString::fromStdString(message), QMessageBox::Warning);
            return false;
        }
    }

    return true;
}

void MapWidget::sincronizarMapaYVista() {
    mapa->limpiar();
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

void MapWidget::mostrarWarning(QString message, QMessageBox::Icon icon) {
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

void MapWidget::pintarParedes(QString object_name) {
    std::string imagen = mapa_recursos.at(object_name.toStdString());
    int filas = mapa->getFilas();
    int columnas = mapa->getColumnas();
    for (int c=0; c < columnas; c++) {
        std::string pos_primera_fila = "pos_0_" + std::to_string(c);
        std::string pos_ultima_fila = "pos_" + std::to_string(filas-1)
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

    for (int f=0; f < filas; f++) {
        std::string pos_primera_columna = "pos_" + std::to_string(f) + "_0";
        std::string pos_ultima_columna = "pos_" + std::to_string(f)
            + "_" + std::to_string(columnas-1);
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