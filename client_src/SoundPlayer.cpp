#include "SoundPlayer.h"

#include <utility>
#include <map>

SoundPlayer::SoundPlayer(){
    const std::string SOUNDS_PATH = "../data/sounds/";
    Sound* dog_bite_sound = new Sound(SOUNDS_PATH+"dog_bite.wav", 100);
    _sounds.insert(std::pair<sound_type, Sound*>(sound_type::DOG_BITE, dog_bite_sound));
    Sound* pistol_shoot_sound = new Sound(SOUNDS_PATH+"pistol_shoot.wav", 100);
    _sounds.insert(std::pair<sound_type, Sound*>(sound_type::PISTOL_SHOOT, pistol_shoot_sound));
}

void SoundPlayer::playSound(SoundPlayer::sound_type sound_type){
    auto sound = _sounds.at(sound_type);
    sound->play();
}

SoundPlayer::~SoundPlayer(){
    for (auto& sound : _sounds){
        delete sound.second;
    }
}
