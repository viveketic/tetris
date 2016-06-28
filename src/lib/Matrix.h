#ifndef TETRIS_MATRIX_H
#define TETRIS_MATRIX_H

#define NO_OF_ROWS 20
#define NO_OF_COLUMNS 10

#include <array>
#include "Common.h"
#include "Tetromino.h"

namespace Tetris
{
    struct Square
    {
        Square()
            :_color(0, 0, 0),
             _isSet(false)
        {}

        Color                   _color;
        bool                    _isSet;
    };

    struct Matrix
    {
        typedef std::array<std::array<Square, NO_OF_COLUMNS>, NO_OF_ROWS> Square2DArray;
        typedef std::array<Tetromino::RelativeSquarePosition, 4> RelativeSquarePositionArray;

        Matrix();
        Square operator()(unsigned row_, unsigned column_) const { return _square2DArray[row_][column_]; }

        unsigned deletePackedRows();

        std::array<unsigned, NO_OF_ROWS> getPackedRows() const;

        unsigned getNoOfRows() const { return NO_OF_ROWS;}
        unsigned getNoOfColumns() const { return NO_OF_COLUMNS;}
        void clear();

        bool isTetrominoMovable(const Tetromino& tetromino_,
                                Tetromino::Action action_,
                                const Position& position_) const;

        void addTetromino(const Tetromino& tetromino_,const Position& position_);
/*
        void moveTetromino(const Tetromino& tetromino_, 
                           const Position& oldPosition_,
                           const Position& newPosition_);
*/
        void showGrid();
        bool hasTetrominoHitHeap(const Tetromino& tetromino_,const Position& position_) const;
        bool hasTetrominoHitBottom(const Tetromino& tetromino_,const Position& position_) const;
        void deleteTetrmino(const Tetromino& tetromino_,const Position& position_);
        void addTetrominoToHeap(const Tetromino& tetromino_, const Position& position_);

    private:
        bool doesTetrominoExistHere(const Tetromino& tetromino_, const Position& position_) const;
        void moveTopRowsDown(unsigned fromRow_);

        Square2DArray                               _square2DArray; 
    };
}


#endif
