#include <QFrame>
#include <QtWidgets>
#include <Qt>

#ifndef RESOURCESWIDGET_H
#define RESOURCESWIDGET_H


class ResourcesWidget : public QFrame
{
 public:
    explicit ResourcesWidget(QWidget *parent = nullptr);

 protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif  // RESOURCESWIDGET_H