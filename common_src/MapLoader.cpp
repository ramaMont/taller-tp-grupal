#include "MapLoader.h"

#include <vector>
#include <string>
#include <iostream>
#include <dirent.h>
#include "string.h"

const std::string MAPS_PATH("../data/maps/");

MapLoader::MapLoader(const std::string& file) : file_name(file){
    std::string command = "md5sum " + MAPS_PATH + file;
    std::string result = executeProgram(command);
    std::string std_checksum = result.substr(28,4);
    checksum = stoi(std_checksum, 0, 16);
}

MapLoader::MapLoader(uint16_t map_id_checksum){
    checksum = -1;
    struct dirent *d;
    DIR *dr;
    std::vector<std::string> files;
    dr = opendir(MAPS_PATH.c_str());
    if (dr == NULL){
        std::cout<<"Error Occurred!\n";
        throw -1;
    }

    for (d=readdir(dr); d!=NULL; d=readdir(dr)){
        if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
            continue;
        else
            files.push_back(d->d_name);
    }
    closedir(dr);
    
    for (auto &file : files){
        std::string command = "md5sum " + MAPS_PATH + file;
        std::string result = executeProgram(command);
        std::string std_checksum = result.substr(28,4);
        uint16_t file_checksum = stoi(std_checksum, 0, 16);
        if (file_checksum == map_id_checksum){
            file_name = file;
            checksum = file_checksum;
            break;
        }
    }
}

uint16_t MapLoader::getChecksum(){
    return checksum;
}

std::string MapLoader::getFileName(){
    if (checksum == -1)
        throw -1;
    return file_name;
}

MapLoader::~MapLoader(){
}

std::string MapLoader::executeProgram(std::string program){
    char buffer[128];
    std::string result = "";

    FILE* pipe = popen(program.c_str(), "r");
    if (!pipe) {
        return "popen failed!";
    }

    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}
