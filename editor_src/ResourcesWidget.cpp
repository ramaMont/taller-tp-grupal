#include "ResourcesWidget.h"
#include <iostream>
#include <QObject>
#include "Editor.h"
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QApplication>

ResourcesWidget::ResourcesWidget(QWidget *parent)
    : QFrame(parent) {
    setAcceptDrops(false);
}

void ResourcesWidget::mousePressEvent(QMouseEvent *event) {
    // Obtengo el elemento clickeado
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    // Preparo la data a guardar en el clipboard (imagen y elemento)
    const QPixmap* pixmap = child->pixmap();
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << *pixmap << QPoint(event->pos() - child->pos());
    QMimeData *mimeData = new QMimeData;
    QString text = child->objectName();
    mimeData->setData("application/x-dnditemdata", itemData);
    mimeData->setText(text);

    // Chequeo si el clipboard tiene data actual, en ese caso la limpio.
    if (QApplication::clipboard()->mimeData()->hasText()) {
        QApplication::clipboard()->clear();
        QApplication::restoreOverrideCursor();
    }
    // Coloco en el clipboard toda mi data.
    QApplication::clipboard()->setMimeData(mimeData);

    // Actualizo el cursor.
    QCursor c = QCursor(*pixmap);
    QApplication::setOverrideCursor(c);
}