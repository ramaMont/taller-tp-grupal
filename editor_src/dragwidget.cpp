#include <QtWidgets>
#include "dragwidget.h"


DragWidget::DragWidget(QWidget *parent, bool accept_drops)
    : QFrame(parent) {
    setAcceptDrops(accept_drops);
}

void DragWidget::dragEnterEvent(QDragEnterEvent *event) {
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

void DragWidget::dragMoveEvent(QDragMoveEvent *event) {
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event-> setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}


void DragWidget::dropEvent(QDropEvent *event) {

}


void DragWidget::mousePressEvent(QMouseEvent *event) {

}