#include "Matrix.h"
#include <iostream>

namespace Tetris
{
    Matrix::Matrix()
    {
        clear();
    }

    void Matrix::clear()
    {
        for(unsigned i = 0; i < NO_OF_ROWS; i++)
        {
            for(unsigned j = 0; j < NO_OF_COLUMNS; j++)
            {
                _square2DArray[i][j]._isSet = false;
            }
        }
    }
    
    bool Matrix::isTetrominoMovable(const Tetromino& tetromino_,
                                    Tetromino::Action action_,
                                    const Position& position_) const
    {
        Tetromino tetromino = tetromino_;
        Position tetrominoPosition = position_;
        switch(action_)
        {
        case Tetromino::Action::ROTATE:
            tetromino.rotate();
            break;
        case Tetromino::Action::MOVE_LEFT:
            tetrominoPosition._column--;
            break;
        case Tetromino::Action::MOVE_RIGHT:
            tetrominoPosition._column++;
            break;
        case Tetromino::Action::MOVE_DOWN:
            tetrominoPosition._row++;
            break;
        }
        
        std::array<Tetromino::RelativeSquarePosition, 4> relativeSquarePositionArray = 
            tetromino.getRelativeSquarePositionArray();

        for(unsigned i = 0; i < relativeSquarePositionArray.size(); i++)
        {
            if((tetrominoPosition._column+relativeSquarePositionArray[i]._column < 0) ||
               (tetrominoPosition._column+relativeSquarePositionArray[i]._column >= NO_OF_COLUMNS) ||
               (tetrominoPosition._row+relativeSquarePositionArray[i]._row < 0) ||
               (tetrominoPosition._row+relativeSquarePositionArray[i]._row >= NO_OF_ROWS))
            {
                return false;
            }
        }
        return true;
    }

    void Matrix::deleteTetrmino(const Tetromino& tetromino_, const Position& position_)
    {
        Color backgroundColor(250, 248, 239);
        RelativeSquarePositionArray relativeSquarePositionArray = 
            tetromino_.getRelativeSquarePositionArray();

        for(unsigned i = 0; i < relativeSquarePositionArray.size(); i++)
        {
            _square2DArray[position_._row+relativeSquarePositionArray[i]._row]
                [position_._column+relativeSquarePositionArray[i]._column]._isSet = false;

            _square2DArray[position_._row+relativeSquarePositionArray[i]._row]
                [position_._column+relativeSquarePositionArray[i]._column]._color = backgroundColor;
        }
        
    }

    void Matrix::addTetromino(const Tetromino& tetromino_,const Position& position_)
    {
        RelativeSquarePositionArray relativeSquarePositionArray = 
            tetromino_.getRelativeSquarePositionArray();

        for(unsigned i = 0; i < relativeSquarePositionArray.size(); i++)
        {
            _square2DArray[position_._row+relativeSquarePositionArray[i]._row]
                [position_._column+relativeSquarePositionArray[i]._column]._isSet = true;

            _square2DArray[position_._row+relativeSquarePositionArray[i]._row]
                [position_._column+relativeSquarePositionArray[i]._column]._color = tetromino_.getColor();
        }
    }
 
    bool Matrix::hasTetrominoHitHeap(const Tetromino& tetromino_,const Position& position_) const
    {
        RelativeSquarePositionArray relativeSquarePositionArray = 
            tetromino_.getRelativeSquarePositionArray();

        for(unsigned i = 0; i < relativeSquarePositionArray.size(); i++)
        {
            if(!doesTetrominoExistHere(
                   tetromino_,Position(relativeSquarePositionArray[i]._row +1,
                                       relativeSquarePositionArray[i]._column)) &&
               _square2DArray[position_._row+relativeSquarePositionArray[i]._row +1]
               [position_._column+relativeSquarePositionArray[i]._column]._isSet)
            {
                return true;
            }
        }
        return false;
    }

    bool Matrix::doesTetrominoExistHere(const Tetromino& tetromino_,const Position& position_) const
    {
        RelativeSquarePositionArray relativeSquarePositionArray = 
            tetromino_.getRelativeSquarePositionArray();

        for(unsigned i = 0; i < relativeSquarePositionArray.size(); i++)
        {
            if(relativeSquarePositionArray[i]._row == position_._row &&
               relativeSquarePositionArray[i]._column == position_._column)
            {
                return true;
            }
        }
        return false;
    }

    bool Matrix::hasTetrominoHitBottom(const Tetromino& tetromino_,const Position& position_) const
    {
        RelativeSquarePositionArray relativeSquarePositionArray = 
            tetromino_.getRelativeSquarePositionArray();

        for(unsigned i = 0; i < relativeSquarePositionArray.size(); i++)
        {
            if((position_._row+relativeSquarePositionArray[i]._row +1 >= NO_OF_ROWS))
            {
                return true;
            }
        }
        return false;
    }

    void Matrix::addTetrominoToHeap(const Tetromino& tetromino_, const Position& position_)
    {
        RelativeSquarePositionArray relativeSquarePositionArray = 
            tetromino_.getRelativeSquarePositionArray();

        for(unsigned i = 0; i < relativeSquarePositionArray.size(); i++)
        {
            _square2DArray[position_._row+relativeSquarePositionArray[i]._row]
                [position_._column+relativeSquarePositionArray[i]._column]._isSet = true;

            _square2DArray[position_._row+relativeSquarePositionArray[i]._row]
                [position_._column+relativeSquarePositionArray[i]._column]._color = tetromino_.getColor();
        }
    }

    unsigned Matrix::deletePackedRows()
    {
        unsigned noOfRowsDeleted = 0;
        for(int row = 0; row < NO_OF_ROWS; row++)
        {
            std::cout << "Row: " << row << std::endl;
            bool isRowPacked = true;
            for(unsigned column = 0; column < NO_OF_COLUMNS; column++)
            {
                if(!_square2DArray[row][column]._isSet)
                {
                    isRowPacked = false;
                    break;
                }
            }
            if(!isRowPacked) continue;

            noOfRowsDeleted++;
            //Clear all squares in the row
            for(unsigned column = 0; column < NO_OF_COLUMNS; column++)
            {
                _square2DArray[row][column]._isSet = false;
            }
            moveTopRowsDown(row);
        }
        return noOfRowsDeleted;
    }

    void Matrix::moveTopRowsDown(unsigned fromRow_)
    {
        for(int row = fromRow_; row >=1; row--)
        {
            for(unsigned column = 0; column < NO_OF_COLUMNS; column++)
            {
                _square2DArray[row][column]._isSet = _square2DArray[row-1][column]._isSet;
                _square2DArray[row][column]._color = _square2DArray[row-1][column]._color;
            }
        }
    }
}
