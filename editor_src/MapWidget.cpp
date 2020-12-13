#include "MapWidget.h"
#include <iostream>
#include <QObject>
#include "Editor.h"
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QApplication>

MapWidget::MapWidget(QWidget *parent)
    : QFrame(parent) {
    setAcceptDrops(true);
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

void MapWidget::desplegarMenuOpciones(QMouseEvent *event, QLabel* label_visual,
                                      QLabel* label_elemento) {
    QMenu contextMenu;
    contextMenu.addAction("Insertar columna a la izquierda", this, [=] {
        std::cout << "IZQ" << std::endl;
    });
    contextMenu.addAction("Insertar columna a la derecha", this, [=] {
        std::cout << "DER" << std::endl;
    });
    contextMenu.addAction("Insertar fila arriba", this, [=] {
        std::cout << "ARR" << std::endl;
    });
    contextMenu.addAction("Insertar fila abajo", this, [=] {
        std::cout << "ABJ" << std::endl;
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

void MapWidget::newRow() {
    std::cout << "New Row" << std::endl;
}