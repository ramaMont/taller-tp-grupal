#include "ResourcesWidget.h"
#include <iostream>
#include <QObject>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QApplication>

ResourcesWidget::ResourcesWidget(QWidget *parent,
                                const std::map<std::string, std::string>&
                                    gameResources, MapWidget* map)
    : QFrame(parent), map(map), gameResources(gameResources) {
    this->setObjectName(QStringLiteral("resourcesWidget"));
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    // Recorro los recursos y por cada uno genero un label.
    for (auto const& element : gameResources) {
        QLabel* label = new QLabel(this);
        label->setObjectName(QString::fromStdString(element.first));
        label->setPixmap(QPixmap(QString::fromStdString(element.second)));
        label->setFixedWidth(MIN_WIDTH_SIZE);
        label->setFixedHeight(MIN_HEIGHT_SIZE);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->setStyleSheet("QWidget:hover{background-color:#D9FAC5;}");
        verticalLayout->addWidget(label);
    }

    setAcceptDrops(false);
}

void ResourcesWidget::mousePressEvent(QMouseEvent *event) {
    // Obtengo el element clickeado
    if (!map->createdMap()) return;

    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QString object_name = child->objectName();

    if ((event->button() == Qt::RightButton) &&
        (object_name.startsWith("wall"))) {
        // Si es click der y es una pared mostrar la opt de pintar bordes.
        QMenu contextMenu;
        contextMenu.addAction("Pared principal", this, [=] {
            map->paintWalls(object_name);
        });
        QPoint globalPos = mapToGlobal(event->pos());
        contextMenu.exec(globalPos);
        return;
    }

    // Preparo la data a guardar en el clipboard (imagen y element)
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
