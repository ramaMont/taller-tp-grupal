#include "BackgroundMusic.h"

#include <cstdlib>
#include <dirent.h>
#include <vector>
#include <iostream>
#include <string>
#include "SDL2/SDL_mixer.h"

const int BACK_MUSIC_CHANNEL = 1;

BackgroundMusic::BackgroundMusic(): paused(false){
    const std::string BACK_MUSIC_PATH = "../data/background_music/";
    struct dirent *d;
    DIR *dr;
    // Reservo 2 canales para la musica de fondo
    int reserved_count = Mix_ReserveChannels(2);
    if (reserved_count != 2) {
        std::cout << "2 channels were not reserved!\n"; 
        // this might be a critical error... 
        throw ("Critical error initializing sound\n");
    } 
    dr = opendir(BACK_MUSIC_PATH.c_str());
    if (dr == NULL){
        std::cout<<"Error Occurred!\n";
        throw -1;
    }

    for (d=readdir(dr); d!=NULL; d=readdir(dr)){
        if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0){
            continue;
        } else {
            Sound* sound = new Sound(BACK_MUSIC_PATH + d->d_name);
            _music_sound_files.push_back(sound);
        }
    }
    closedir(dr);
}

void BackgroundMusic::playMusic(){
    if (Mix_Playing(BACK_MUSIC_CHANNEL) == 0 && !paused){
        int rand_track_number = rand() % _music_sound_files.size();
        _music_sound_files.at(rand_track_number)->play(75, BACK_MUSIC_CHANNEL);
    }
}

void BackgroundMusic::togglePause(){
    if (paused){
        paused = false;
        Mix_Resume(BACK_MUSIC_CHANNEL);
    } else {
        paused = true;
        Mix_Pause(BACK_MUSIC_CHANNEL);
    }
}

BackgroundMusic::~BackgroundMusic(){
    for (auto sound : _music_sound_files){
        delete sound;
    }
}
