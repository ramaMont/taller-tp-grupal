#ifndef EDITOR_H
#define EDITOR_H

#include <string>
#include <iostream>
#include <QApplication>
#include <QMouseEvent>
#include <QtWidgets>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMimeData>
#include <QPainter>
#include <QDrag>
#include <map>
#include <QGridLayout>
#include <QStandardItemModel>
#include <QVariant>
#include <QScrollArea>
#include <QMessageBox>
#include "ResourcesWidget.h"
#include "MapWidget.h"

class Editor : public QWidget {
public:
    explicit Editor(QWidget *parent = 0);

private:
    QMessageBox* messageBox;
    QHBoxLayout *createMapHLayout;
    QWidget *createMapWidget;
    QWidget *resourcesWidget;
    QScrollArea *scrollMapArea;
    QScrollArea *scrollResourcesArea;
    QLabel* rowLabel;
    QLabel* columnsLabel;
    MapWidget *mapWidget;
    std::map<std::string, std::string> gameResources;
    void createNewMap();
    void loadMapFile();
    void createMenu();
    void saveMap();
    void keyPressEvent(QKeyEvent* event) override;
    bool eventFilter(QObject *obj, QEvent *event);
    bool showFileDialog();
    void setScrollBarStyle(QScrollArea* scrollArea);
    void insertInResourcesMap(std::map<std::string, std::string>& map,
                              std::string key, std::string value);
    void closeEvent(QCloseEvent *event);
    std::map<std::string, std::string> getResourcesMap();
};

#endif // EDITOR_H
