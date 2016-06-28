#include "Painter.h"

namespace Tetris
{
    void Painter::drawRectangle(unsigned x_,
                                unsigned y_,
                                unsigned width_,
                                unsigned height_,
                                unsigned thickness_,
                                const Color& borderColor_,
                                const Color& fillColor_) const
    {
        SDL_Rect rectangle;

        rectangle.x = x_;
        rectangle.y = y_;
        rectangle.w = width_;
        rectangle.h = height_;

        //This fills the rectangle
        SDL_Rect temp = rectangle;
        temp.x += thickness_;
        temp.y += thickness_;
        temp.w -= 2*thickness_;
        temp.h -= 2*thickness_;
        SDL_SetRenderDrawColor(_renderer,
                               fillColor_._red,
                               fillColor_._green,
                               fillColor_._blue,
                               255);
        SDL_RenderFillRect(_renderer, &temp);

        //This draws the border of rectangle
        for(unsigned i = 0; i < thickness_; i++)
        {
            rectangle.x += i;
            rectangle.y += i;
            rectangle.w -= 2*i;
            rectangle.h -= 2*i;
            
            SDL_SetRenderDrawColor(_renderer, 
                                   borderColor_._red, 
                                   borderColor_._green, 
                                   borderColor_._blue, 
                                   255);

            SDL_RenderDrawRect(_renderer, &rectangle);
        }

    }
}
