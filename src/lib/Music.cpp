#include "Music.h"

#include <iostream>

namespace Tetris
{
    bool Music::init()
    {
        //Initialize SDL_mixer
        if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
        {
            std::cout << "Error-failed intializing mixer" << std::endl;
            std::exit(1);
        }

        //Load all sound effects
        _soundMap[Sound::ROTATE] = Mix_LoadWAV("sounds/block-rotate.wav");
        _soundMap[Sound::LINE_REMOVAL] = Mix_LoadWAV("sounds/line-remove.wav");
        _soundMap[Sound::FORCE_HIT] = Mix_LoadWAV("sounds/force-hit.wav");

        for(auto const &sound: _soundMap)
        {
            if(NULL == sound.second) return false;
        }
        return true;
    }

    bool Music::playSound(Sound sound)
    {
        if(Mix_PlayChannel(-1,_soundMap[sound],0) == -1)
        {
            std::cout << "ERROR-1" << std::endl;
            return false;
        }   
        return true;
    }

    void Music::exit()
    {
        //Unload all sound effects
        for(auto const &sound: _soundMap)
        {
            Mix_FreeChunk(sound.second);
        }

        Mix_CloseAudio();
    }

}
