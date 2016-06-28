#ifndef TETRIS_COMMON_H
#define TETRIS_COMMON_H

#define NO_OF_TETROMINO_SHAPES 7
#define TETROMINO_START_ROW 1
#define TETROMINO_START_COLUMN 5

namespace Tetris
{
    struct Color
    {
        Color(unsigned red_,
              unsigned green_,
              unsigned blue_)
            :_red(red_),
             _green(green_),
             _blue(blue_)
        {}
            
        unsigned                      _red;
        unsigned                      _green;
        unsigned                      _blue;
    };

    struct Position
    {
        Position(){}
        Position(int row_, int column_)
            :_row(row_),
             _column(column_)
        {}

        int                                _row;
        int                                _column;
    };

    struct Cordinate
    {
        Cordinate(unsigned x_, unsigned y_)
            : _x(x_),
              _y(y_)
        {}

        unsigned                           _x;
        unsigned                           _y;
    };

//    void pauseTime(unsigned milliSeconds_) const { return SDL_Delay(milliSeconds_);}
}

#endif
