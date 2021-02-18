#include <QFrame>
#include <QtWidgets>
#include <Qt>
#include <QContextMenuEvent>
#include <string>
#include <QGridLayout>
#include <QMessageBox>
#include <QMainWindow>
#include <iostream>
#include <map>
#include "EditableMap.h"

#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#define MIN_WIDTH_SIZE 80
#define MIN_HEIGHT_SIZE 80
#define MESSAGEBOX_TYPE_INFO 0
#define MESSAGEBOX_TYPE_ALERT 1

class MapWidget : public QFrame
{
 public:
    explicit MapWidget(QWidget *parent,
                       const std::map<std::string, std::string>& resourcesMap);
    ~MapWidget();
    bool createdMap();
    bool savedMap();
    void constructMap(const int& flag);
    void saveMap();
    void createNewMap(const std::string& name,
                        const int& rows, const int& columns);
    void loadMapFromFile(const std::string& map_file);
    void updateWindowName();
    void updateLabelRC();
    void paintWalls(QString object_name);
    void cleanGridAndMap();
    void showWarning(QString message, QMessageBox::Icon icon);
    void cleanHighlightedLabel();

 protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

 private:
    EditableMap* map;
    QGridLayout* gridLayout;
    std::map<std::string, std::string> resourcesMap;
    QLabel* highlightedLabel;
    QLabel* originLabel;
    bool mapCreated;
    bool mapSaved;
    void pointAndClick(QLabel* visual_label, QLabel* element_label);
    void showOptionsMenu(QMouseEvent *event, QLabel* visual_label,
                               QLabel* element_label);
    void executeDrag(QMouseEvent *event, QLabel* visual_label,
                      QLabel* element_label);
    void synchronizeMapAndView();
    void addCoumnFrom(int column);
    void addRowFrom(int row);
    void deleteRow(int row);
    void deleteColumn(int row);
    void swapLabels(const std::string& pos_1,
                            const std::string& pos_2);
    void createEmptyCell(const std::string& pos, const int& row,
                         const int& column);
};

#endif  // MAPWIDGET_H