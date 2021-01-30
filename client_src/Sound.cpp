#include "Sound.h"

Sound::Sound(const std::string& file_path, int volume) : 
        mix_chunk(Mix_LoadWAV(file_path.c_str()), Mix_FreeChunk){
    if (!mix_chunk.get()){
        throw ("Couldn't open file: "+ file_path + "\n");
    }
    Mix_VolumeChunk(mix_chunk.get(), volume);
}

void Sound::play() {
    Mix_PlayChannel(-1, mix_chunk.get(), 0);
}

void Sound::setVolume(int volume) {
    Mix_VolumeChunk(mix_chunk.get(), volume);
}

Sound::~Sound(){
}