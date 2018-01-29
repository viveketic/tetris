#include <iostream>
#include <string>
#include <sstream>

#include "TetrisPainter.h"


namespace Tetris
{
    TetrisPainter::TetrisPainter(SDL_Renderer* renderer_,
                                 unsigned screenWidth_,
                                 unsigned screenHeight_)
        :MyBase(renderer_),
         _screenWidth(screenWidth_),
         _screenHeight(screenHeight_)
    {
        if(-1 == TTF_Init()) {
            printf("TTF_Init: %s\n", TTF_GetError());
            exit(2);
        }
    }

    void TetrisPainter::drawButton(std::string& text_, 
                                   unsigned x_,
                                   unsigned y_,
                                   unsigned width_,
                                   unsigned height_,
                                   const Color& borderColor_,
                                   const Color& fillColor_) const
    {
        //this opens a font style and sets a size

        drawRectangle(x_, y_, width_, height_, 1, borderColor_, fillColor_);
    }

    void TetrisPainter::drawPanel(unsigned score_, const Tetromino& nextTetromino_) const
    {
        double panelWidth = 200;
        Color borderColor(192,163,95); //panel border color
        Color fillColor(252, 245, 210); //panel fill color

        drawRectangle(0, 0,
                      panelWidth, _screenHeight,
                      2, 
                      borderColor, fillColor);

        std::string text = "New Game";
        /* 
         * drawButton(text, 30, 30, 160, 40, borderColor, fillColor);
         * drawButton(text, 30, 71, 160, 40, borderColor, fillColor);
         */
        drawTetrominoOnPanel(Cordinate(100,200), nextTetromino_);

        std::ostringstream ss;
        ss << "Score: " << score_;
        drawText(ss.str(),13,Cordinate(60,230),borderColor);


        SDL_RenderPresent(_renderer);       
    }

    Cordinate TetrisPainter::
    getCordinateFromSquarePosition(unsigned row_, unsigned column_) const
    {
        double squareSize = 20;
        double panelWidth = 200;

        return Cordinate((column_-1)*squareSize + panelWidth,(row_-1)*squareSize);
    }

    Cordinate TetrisPainter::
    getCordinateFromRelativeSquarePosition(unsigned row_, unsigned column_) const
    {
        double squareSize = 20;
        double panelWidth = 200;

        return Cordinate((column_-1)*squareSize,(row_-1)*squareSize);
    }

    void TetrisPainter::drawMatrix(const Matrix& matrix_) const
    {
        for(unsigned i = 1; i <= matrix_.getNoOfRows(); i++)
        {
            for(unsigned j = 1; j <= matrix_.getNoOfColumns(); j++)
            {
                drawSquare(matrix_(i-1, j-1), i, j);
            }
        }
        SDL_RenderPresent(_renderer);       
    }

    void TetrisPainter::drawSquare(const Square& square_,unsigned row_,unsigned column_) const
    {
        Cordinate squareCordinate = getCordinateFromSquarePosition(row_, column_);

        double squareSize = 20;
        Color borderColor(82, 82, 82);
        Color backgroundColor(255, 250, 235);
        if(square_._isSet)
        {
            drawRectangle(squareCordinate._x, 
                          squareCordinate._y,
                          squareSize, squareSize,
                          1,
                          borderColor, square_._color);
        }
        else
        {
            drawRectangle(squareCordinate._x, 
                          squareCordinate._y,
                          squareSize, squareSize,
                          0,
                          borderColor, backgroundColor);
        }
    }

    void TetrisPainter::clearMatrix() const
    {
        double matrixWidth = 200;
        Color borderColor(82, 82, 82); //matrix border
        Color fillColor(255, 250, 235); //matrix background color
        drawRectangle(200, 0,
                      matrixWidth, _screenHeight,
                      2, 
                      borderColor, fillColor);
    }

    void TetrisPainter::
    drawTetrominoOnPanel(const Cordinate& cordinate_,const Tetromino& tetromino_) const
    {
        Tetromino::RelativeSquarePositionArray relativeSquarePositionArray = 
            tetromino_.getRelativeSquarePositionArray();

        for(unsigned i = 0; i < relativeSquarePositionArray.size(); i++)
        {
            Cordinate squareCordinate = 
                getCordinateFromRelativeSquarePosition(
                    relativeSquarePositionArray[i]._row, 
                    relativeSquarePositionArray[i]._column);

            double squareSize = 20;
            Color borderColor(82, 82, 82);
            drawRectangle(cordinate_._x+squareCordinate._x, 
                          cordinate_._y+squareCordinate._y,
                          squareSize, squareSize,
                          1,
                          borderColor, 
                          tetromino_.getColor());
        }
    }

    void TetrisPainter::
    drawText(const std::string& text_, unsigned fontSize_, 
             const Cordinate& cordinate_, const Color& color_) const
    {
        TTF_Font* ttfFont = TTF_OpenFont("res/sans.ttf", fontSize_);
        if(!ttfFont)
        {
            printf("TTF_OpenFont: %s\n", TTF_GetError());
            return;
        }
        TTF_SetFontStyle(ttfFont, TTF_STYLE_BOLD);
        SDL_Color textColor = {color_._red,color_._green,color_._blue,0};

        SDL_Surface* textSurface = 
            TTF_RenderText_Solid(ttfFont, text_.c_str(), textColor);

        SDL_Texture* text = SDL_CreateTextureFromSurface(_renderer, textSurface); 

        int x = cordinate_._x;
        int y = cordinate_._y;
        SDL_Rect text_rect = {x,y, textSurface->w, textSurface->h};

        SDL_RenderCopy(_renderer, text, NULL, &text_rect);
        SDL_DestroyTexture(text);
    }
}
