#ifndef __SOUND_PLAYER__
#define __SOUND_PLAYER__

#include <map>
#include "Sound.h"

class SoundPlayer{
public:
    enum sound_type{
        PISTOL_SHOOT, MACHINEGUN_SHOOT, CHAINGUN_SHOOT, DOG_BITE, 
        ROCKET_LAUNCHER, DOOR_OPENING, DOOR_CLOSING, DYING, 
        ROCKET_EXPLOTION
    };
    SoundPlayer();
    void playSound(SoundPlayer::sound_type sound_type, int volume);
    void playSoundAtDistance(SoundPlayer::sound_type sound_type, 
        float distance);
    // Calcula el volumen usando una funcion exponencial
    int calculateVolume(float distance);
    ~SoundPlayer();
private:
    std::map<sound_type, Sound*> _sounds;
};

#endif
