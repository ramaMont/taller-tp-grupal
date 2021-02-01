#ifndef __BACK_MUSIC__
#define __BACK_MUSIC__

#include <string>
#include <vector>
#include "Sound.h"

class BackgroundMusic{
private:
    std::vector<Sound*> _music_sound_files;
    bool paused;
public:
    BackgroundMusic();
    void playMusic();
    void togglePause();
    ~BackgroundMusic();
};

#endif
