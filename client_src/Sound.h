#ifndef __SOUND__
#define __SOUND__

#include <memory>
#include <string>
#include <SDL2/SDL_mixer.h>


class Sound{
private:
    std::unique_ptr<Mix_Chunk, void (*)(Mix_Chunk *)> mix_chunk;
public:
    explicit Sound(const std::string& file_path, int volume);
    void play();
    void setVolume(int volume);
    ~Sound();
};

#endif
