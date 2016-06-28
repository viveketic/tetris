#include "Tetromino.h"
#include <iostream>

namespace Tetris
{
    Tetromino::Tetromino(Shape shape_, const Color& color_)
        :_color(color_),
         _shape(shape_),
         _relativeSquarePositionArray(calculateRelativeSquarePositionArray())
    {}

    void Tetromino::rotate()
    {
        if(Shape::O == _shape)
        {
            return;
        }
        std::cout << "rotate"
                  << std::endl;
/*
        int terominoShapeValue = static_cast<int>(_shape);
        terominoShapeValue = ((terominoShapeValue+1) % 4);
        _shape = static_cast<Shape>(terominoShapeValue);
*/
        for(unsigned i = 0; i < _relativeSquarePositionArray.size(); i++)
        {
            int tempColumn = _relativeSquarePositionArray[i]._column;
            _relativeSquarePositionArray[i]._column = 
                _relativeSquarePositionArray[i]._row * -1;
            _relativeSquarePositionArray[i]._row = tempColumn;

            std::cout << "Row: " 
                      << _relativeSquarePositionArray[i]._row
                      << ", "
                      << _relativeSquarePositionArray[i]._column
                      << std::endl;
        }
    }
    
    Tetromino::RelativeSquarePositionArray 
    Tetromino::calculateRelativeSquarePositionArray() const
    {
        //Create empty RelativeSquarePositionArray
        RelativeSquarePositionArray relativeSquarePositionArray =
        {
            RelativeSquarePosition(0,0),
            RelativeSquarePosition(0,0),
            RelativeSquarePosition(0,0),
            RelativeSquarePosition(0,0)
        };

        switch(_shape)
        {
        case Shape::I:
            relativeSquarePositionArray[0] = RelativeSquarePosition(0, -1);
            relativeSquarePositionArray[1] = RelativeSquarePosition(0, 0);
            relativeSquarePositionArray[2] = RelativeSquarePosition(0, 1);
            relativeSquarePositionArray[3] = RelativeSquarePosition(0, 2);
            break;
        case Shape::J:
            relativeSquarePositionArray[0] = RelativeSquarePosition(0, -1);
            relativeSquarePositionArray[1] = RelativeSquarePosition(0, 0);
            relativeSquarePositionArray[2] = RelativeSquarePosition(0, 1);
            relativeSquarePositionArray[3] = RelativeSquarePosition(1, 1);
            break;
        case Shape::L:
            relativeSquarePositionArray[0] = RelativeSquarePosition(0, -1);
            relativeSquarePositionArray[1] = RelativeSquarePosition(0, 0);
            relativeSquarePositionArray[2] = RelativeSquarePosition(0, 1);
            relativeSquarePositionArray[3] = RelativeSquarePosition(1, -1);
            break;
        case Shape::O:
            relativeSquarePositionArray[0] = RelativeSquarePosition(0, 0);
            relativeSquarePositionArray[1] = RelativeSquarePosition(0, 1);
            relativeSquarePositionArray[2] = RelativeSquarePosition(1, 0);
            relativeSquarePositionArray[3] = RelativeSquarePosition(1, 1);
            break;
        case Shape::S:
            relativeSquarePositionArray[0] = RelativeSquarePosition(0, 0);
            relativeSquarePositionArray[1] = RelativeSquarePosition(0, 1);
            relativeSquarePositionArray[2] = RelativeSquarePosition(1, -1);
            relativeSquarePositionArray[3] = RelativeSquarePosition(1, 0);
            break;
        case Shape::T:
            relativeSquarePositionArray[0] = RelativeSquarePosition(0, -1);
            relativeSquarePositionArray[1] = RelativeSquarePosition(0, 0);
            relativeSquarePositionArray[2] = RelativeSquarePosition(0, 1);
            relativeSquarePositionArray[3] = RelativeSquarePosition(1, 0);
            break;
        case Shape::Z:
            relativeSquarePositionArray[0] = RelativeSquarePosition(0, -1);
            relativeSquarePositionArray[1] = RelativeSquarePosition(0, 0);
            relativeSquarePositionArray[2] = RelativeSquarePosition(1, 0);
            relativeSquarePositionArray[3] = RelativeSquarePosition(1, 1);
            break;
        }
        return relativeSquarePositionArray;
    }
}
