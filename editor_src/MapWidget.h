#include <QFrame>
#include <QtWidgets>
#include <Qt>
#include <QContextMenuEvent>

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
    void newRow();
    void pointAndClick(QLabel* label_visual, QLabel* label_elemento);
    void desplegarMenuOpciones(QMouseEvent *event, QLabel* label_visual,
                               QLabel* label_elemento);
    void ejecutarDrag(QMouseEvent *event, QLabel* label_visual,
                      QLabel* label_elemento);
};

#endif  // MAPWIDGET_H