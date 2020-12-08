#include <QFrame>
#include <QtWidgets>
#include <Qt>

#ifndef MAPWIDGET_H
#define MAPWIDGET_H


class MapWidget : public QFrame
{
 public:
    explicit MapWidget(QWidget *parent = nullptr);

 protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif  // MAPWIDGET_H