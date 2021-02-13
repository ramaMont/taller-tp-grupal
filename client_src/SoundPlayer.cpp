#include "SoundPlayer.h"

#include <utility>
#include <map>
#include <string>

SoundPlayer::SoundPlayer(){
    const std::string SOUNDS_PATH = "../data/sounds/";
    Sound* dog_bite_sound = new Sound(SOUNDS_PATH+"dog_bite.wav");
    _sounds.insert(std::pair<sound_type, Sound*>\
        (sound_type::DOG_BITE, dog_bite_sound));
    Sound* pistol_shoot_sound = new Sound(SOUNDS_PATH+"pistol_shoot.wav");
    _sounds.insert(std::pair<sound_type, Sound*>\
        (sound_type::PISTOL_SHOOT, pistol_shoot_sound));
    Sound* door_opening = new Sound(SOUNDS_PATH+"door_opening.mp3");
    _sounds.insert(std::pair<sound_type, Sound*>\
        (sound_type::DOOR_OPENING, door_opening));
    Sound* door_closing = new Sound(SOUNDS_PATH+"door_closing.mp3");
    _sounds.insert(std::pair<sound_type, Sound*>\
        (sound_type::DOOR_CLOSING, door_closing));
    Sound* dying = new Sound(SOUNDS_PATH+"dying.wav");
    _sounds.insert(std::pair<sound_type, Sound*>\
        (sound_type::DYING, dying));
    Sound* machinegun_shoot = new Sound(SOUNDS_PATH+"mac_gun_shoot.wav");
    _sounds.insert(std::pair<sound_type, Sound*>\
        (sound_type::MACHINEGUN_SHOOT, machinegun_shoot));
    Sound* chaingun_shoot = new Sound(SOUNDS_PATH+"chaingun_shoot.mp3");
    _sounds.insert(std::pair<sound_type, Sound*>\
        (sound_type::CHAINGUN_SHOOT, chaingun_shoot));
    Sound* rocket_launcher = new Sound(SOUNDS_PATH+"rocket_launcher.mp3");
    _sounds.insert(std::pair<sound_type, Sound*>\
        (sound_type::ROCKET_LAUNCHER, rocket_launcher));
    Sound* rocket_explotion = new Sound(SOUNDS_PATH+"explotion.wav");
    _sounds.insert(std::pair<sound_type, Sound*>\
        (sound_type::ROCKET_EXPLOTION, rocket_explotion));
}

void SoundPlayer::playSound(SoundPlayer::sound_type sound_type, int volume){
    auto sound = _sounds.at(sound_type);
    sound->play(volume);
}

void SoundPlayer::playSoundAtDistance(SoundPlayer::sound_type sound_type,
        float distance){
    auto sound = _sounds.at(sound_type);
    sound->play(calculateVolume(distance));
}

int SoundPlayer::calculateVolume(float distance){
    if (distance <= 0)
        return 100;
    return (int)std::floor(std::exp(5.2539 - 0.1188 * distance));
}

SoundPlayer::~SoundPlayer(){
    for (auto& sound : _sounds){
        delete sound.second;
    }
}
