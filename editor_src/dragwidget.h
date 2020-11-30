#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QFrame>
#include <QDragEnterEvent>
#include <QDropEvent>


class DragWidget : public QFrame
{
 public:
    explicit DragWidget(QWidget *parent = nullptr, bool accept_drops = false);

 protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif  // DRAGWIDGET_H