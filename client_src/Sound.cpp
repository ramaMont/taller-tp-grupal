#include "Sound.h"

Sound::Sound(const std::string& file_path) : 
        mix_chunk(Mix_LoadWAV(file_path.c_str()), Mix_FreeChunk){
    if (!mix_chunk.get()){
        throw ("Couldn't open file: "+ file_path + "\n");
    }
}

void Sound::play(int volume, int channel) {
    Mix_VolumeChunk(mix_chunk.get(), volume);
    Mix_PlayChannel(channel, mix_chunk.get(), 0);
}

Sound::~Sound(){
}
