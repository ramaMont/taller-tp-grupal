#include <QFrame>
#include <QtWidgets>
#include <Qt>
#include <map>
#include <string>
#include "MapWidget.h"

#ifndef RESOURCESWIDGET_H
#define RESOURCESWIDGET_H

#define MIN_WIDTH_SIZE 80
#define MIN_HEIGHT_SIZE 80

class ResourcesWidget : public QFrame
{
 public:
    explicit ResourcesWidget(QWidget *parent,
                             const std::map<std::string, std::string>&
                              recursos_del_juego, MapWidget* map);

 protected:
    void mousePressEvent(QMouseEvent *event) override;

 private:
    QVBoxLayout *verticalLayout;
    MapWidget* map;
    std::map<std::string, std::string> recursos_del_juego;
};

#endif  // RESOURCESWIDGET_H