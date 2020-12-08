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


void MapWidget::mousePressEvent(QMouseEvent *event) {
    // Obtengo el label grafico, y el oculto que tiene el elemento.
    QLabel* child = static_cast<QLabel*>(childAt(event->pos()));
    QLabel* child_element = findChild<QLabel*>
                                (child->objectName() + "_element");
    if (!child)
        return;

    if (QApplication::clipboard()->mimeData()->hasText()) {
        // Si habia algo en el clipboard, quiere decir que este click
        // tiene como objetivo pintar, y no hacer el drag & drop.
        QByteArray itemData = QApplication::clipboard()->mimeData()
                              ->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        child->setPixmap(pixmap);
        child_element->setText(QApplication::clipboard()->mimeData()->text());
        return;
    }

    // Si es un elemento vacio, no tiene sentido drag & drop a partir de este.
    if (child_element->text().toStdString() == "vacio") return;

    const QPixmap* pixmap = child->pixmap();

    // Leo lo clickeado
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << *pixmap << QPoint(event->pos() - child->pos());

    // Preparo la data a mover en el drag
    QMimeData *mimeData = new QMimeData;
    QString text = child_element->text();
    mimeData->setData("application/x-dnditemdata", itemData);
    mimeData->setText(text);

    // Preparo el drag
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(*pixmap);
    drag->setHotSpot(event->pos() - child->pos());

    // Ejecuto el drag, y al terminar, limpio el correspondiente.
    drag->exec(Qt::CopyAction | Qt::MoveAction,
               Qt::CopyAction);
    child->setPixmap(QPixmap());
    child_element->setText("vacio");
}