
#ifndef EDITABLEMAP_H
#define EDITABLEMAP_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "map_exceptions.h"

#define MAX_RC 40
#define MIN_Rc 10
#define LOAD_FROM_FILE 1
#define NEW_MAP 0

class EditableMap {
 public:
    EditableMap(const int& flag,
                 const std::string& name,
                 const std::string& mapfile,
                 const int& rows, const int& columns);
    ~EditableMap();
    void loadExistentMap();
    void loadElement(const std::string& position,
                        const std::string& element);
    void updateElement(const std::string& position,
                            const std::string& element);
    void getElement(const std::string& position,
                         std::string& element);
    void saveMap();
    void addRow();
    void addColumn();
    void deleteRow();
    void deleteColumn();
    void validateMap();
    void validateWalls();
    void validateDoors();
    void validatePlayers();
    void addCategory(std::string& element);
    int getColumns();
    int getRows();
    void clean();
    std::string getName();

 private:
    std::map<std::string, std::string> map;
    std::string mapfile;
    std::string name;
    int rows;
    int columns;
};

#endif // EDITABLEMAP_H