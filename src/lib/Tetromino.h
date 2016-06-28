#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H

#include <array>
/*
Tetromino is composed of square blocks. We choose
particular block as pivot.
*/

#include "Common.h"

namespace Tetris
{
    class Tetromino
    {
    public:
        struct RelativeSquarePosition
        {
            RelativeSquarePosition(int row_, int column_)
                :_row(row_),
                 _column(column_)
            {}

            int                         _row;
            int                         _column;
        };

        typedef std::array<RelativeSquarePosition, 4> RelativeSquarePositionArray;
        enum class Shape
        {
            I = 0,
            O = 1,
            T = 2,
            J = 3,
            L = 4,
            S = 5, 
            Z = 6
        };
/*
        enum class Angle
        {
            ANGLE0 = 0,
            ANGLE90 = 1,
            ANGLE180  = 2,
            ANLLE270 = 3
        };
*/
        enum class Action
        {
            ROTATE = 0,
            MOVE_LEFT = 1,
            MOVE_RIGHT = 2,
            MOVE_DOWN = 3
        };
        
        struct BoundaryDistances
        {
            BoundaryDistances(size_t left_,
                             size_t bottom_,
                             size_t right_,
                             size_t top_)
                :_left(left_),
                 _bottom(bottom_),
                 _right(right_),
                 _top(top_)
            {}

            size_t                  _left;
            size_t                  _bottom;
            size_t                  _right;
            size_t                  _top;
        };        

        Tetromino(Shape shape_, const Color& color_);
        void rotate();
        const Shape& getShape() const { return _shape;}
        const RelativeSquarePositionArray& getRelativeSquarePositionArray() const { return _relativeSquarePositionArray;}
        const Color& getColor() const { return _color;}
        const BoundaryDistances& getBoundaryDistances() const;

    private:
        Color                               _color;
        Shape                               _shape;
        RelativeSquarePositionArray         _relativeSquarePositionArray;

        RelativeSquarePositionArray calculateRelativeSquarePositionArray() const;
//        void setColor(const Color& color_) {_color = color_;}
    };
}

#endif
