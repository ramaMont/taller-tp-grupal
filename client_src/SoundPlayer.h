#ifndef __SOUND_PLAYER__
#define __SOUND_PLAYER__

#include <map>
#include "Sound.h"

class SoundPlayer{
public:
    enum sound_type{
        PISTOL_SHOOT, DOG_BITE
    };
    SoundPlayer();
    void playSound(SoundPlayer::sound_type sound_type, int volume);
    int calculateVolume(float distance);
    ~SoundPlayer();
private:
    std::map<sound_type, Sound*> _sounds;
};

#endif
