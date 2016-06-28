#ifndef TETRIS_PAINTER_H
#define TETRIS_PAINTER_H

#include <SDL.h>
#include "Common.h"

namespace Tetris
{
    class Painter
    {
    public:
        Painter(SDL_Renderer* renderer_)
            :_renderer(renderer_)
        {}
        void  drawRectangle(unsigned x_,
                            unsigned y_,
                            unsigned width_,
                            unsigned height_,
                            unsigned thickness_,
                            const Color& borderColor_,
                            const Color& fillColor_) const;

    protected:
        SDL_Renderer*                  _renderer;
    };
}


#endif
