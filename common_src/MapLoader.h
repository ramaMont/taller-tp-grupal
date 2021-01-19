#ifndef __MAP_LOADER__
#define __MAP_LOADER__

#include <string>

class MapLoader{
private:
    std::string file_name;
    uint16_t checksum;
    std::string executeProgram(std::string program);
public:
    explicit MapLoader(std::string path);
    explicit MapLoader(uint16_t map_id_checksum);
    uint16_t getChecksum();
    std::string getFileName();
    ~MapLoader();
};

#endif
