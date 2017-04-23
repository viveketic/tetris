#ifndef TETRIS_MUSIC_H
#define TETRIS_MUSIC_H

#include "SDL_mixer.h"
#include <map>

namespace Tetris
{
    enum class Sound
    {
        ROTATE = 0,
        LINE_REMOVAL = 1,
        FORCE_HIT =2
    };


    class Music
    {
    public:
        bool init();
        bool playSound(Sound sound);
        void exit();

    private:

        std::map<Sound, Mix_Chunk*>           _soundMap;
    };

}

#endif
