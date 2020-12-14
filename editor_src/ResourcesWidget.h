#include <QFrame>
#include <QtWidgets>
#include <Qt>
#include <map>
#include <string>

#ifndef RESOURCESWIDGET_H
#define RESOURCESWIDGET_H

#define MIN_WIDTH_SIZE 80
#define MIN_HEIGHT_SIZE 80

class ResourcesWidget : public QFrame
{
 public:
    explicit ResourcesWidget(QWidget *parent,
                             const std::map<std::string, std::string>&
                              recursos_del_juego);

 protected:
    void mousePressEvent(QMouseEvent *event) override;

 private:
    QVBoxLayout *verticalLayout;
    std::map<std::string, std::string> recursos_del_juego;
};

#endif  // RESOURCESWIDGET_H