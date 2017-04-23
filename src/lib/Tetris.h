#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <cstdlib>
#include <SDL.h>


#include "Matrix.h"
#include "Tetromino.h"
#include "Common.h"
#include <iostream>
#include "Music.h"

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 400

namespace Tetris
{
    class Tetris
    {
    public:
        Tetris();
        void start();        

    private:
        void init();
        void run();
        void exit();
        Tetromino generateRandomTertomino() const;
        void addTetromino();
        void moveTetromino(Tetromino::Action action_);

        SDL_Window*                           _window;
        SDL_Renderer*                         _renderer;
        Position                              _tetrominoPosition;
        unsigned                              _tetrominoCurrentRow;
        unsigned                              _tetrominoCurrentColumn;
        Tetromino                             _tetromino;
        Matrix                                _matrix;
        unsigned                              _score;
        Music                                 _music;
    };

}

#endif
