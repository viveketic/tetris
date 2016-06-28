#ifndef TETRIS_TETRISPAINTER_H
#define TETRIS_TETRISPAINTER_H

#include<string>

#include "Painter.h"
#include "Matrix.h"
#include "Tetromino.h"
#include <SDL_ttf.h>

namespace Tetris
{
    class TetrisPainter: public Painter
    {
    public:
        typedef Painter MyBase;
        TetrisPainter(SDL_Renderer* renderer_,unsigned screenWidth_,unsigned screenHeight_);

        void drawGrid() const;
        void addTetrominoToMatrix(Tetromino tertromino_, 
                                  Matrix& matrix_,
                                  unsigned row_,
                                  unsigned column_) const;

        void drawSquare(const Square& square_, unsigned row_, unsigned column_) const;

        void drawMatrix(const Matrix& matrix_) const;
        
        void drawPanel(unsigned score_, const Tetromino& nextTetromino_) const;

        void drawButton(std::string& text_, 
                        unsigned x_,
                        unsigned y_,
                        unsigned width_,
                        unsigned height_,
                        const Color& borderColor_,
                        const Color& fillColor_) const;
        
        void drawLabel(std::string& text_,
                       unsigned x_,
                       unsigned y_,
                       unsigned width_,
                       unsigned height_) const {}

        void clearMatrix() const;
    private:
        Cordinate getCordinateFromSquarePosition(unsigned row_, unsigned column_) const;
        Cordinate getCordinateFromRelativeSquarePosition(unsigned row_, unsigned column_) const;
        void drawTetrominoOnPanel(const Cordinate& cordinate_,const Tetromino& tetromino_) const;
        void drawText(const std::string& text_, unsigned fontSize_, 
                      const Cordinate& cordinate_, const Color& color_) const;

        unsigned                                _screenWidth;
        unsigned                                _screenHeight;
    };
}


#endif
