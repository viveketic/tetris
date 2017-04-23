#include "Tetris.h"
#include "TetrisPainter.h"

#include <iostream>

namespace Tetris
{
    Tetris::Tetris()
        :_window(NULL),
         _renderer(NULL),
         _tetromino(Tetromino::Shape::I,Color(0,0,0)),
         _matrix(Matrix()),
         _score(0),
         _music()
    {}

    void Tetris::start()
    {
        init();
        run();
        exit();
    }

    void Tetris::init()
    {
        _window = SDL_CreateWindow(
            "Tetris", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);

        _renderer = 
            SDL_CreateRenderer(_window, 0, SDL_RENDERER_ACCELERATED);
 
        SDL_SetRenderDrawColor(_renderer, 250, 248, 239, 255);
        SDL_RenderClear(_renderer);

        std::string buttonText = "New Game";
        TetrisPainter tetrisPainter(_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
        tetrisPainter.drawPanel(0,_tetromino);

        _music.init();
    }

    void Tetris::run()
    {
        //Game loop starts here
        SDL_Event event;
        bool quit = false;

        _tetrominoPosition = Position(1,4);
        _tetromino = generateRandomTertomino();
        addTetromino();
        Tetromino nextTetromino = generateRandomTertomino();
        TetrisPainter tetrisPainter(_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
        tetrisPainter.drawPanel(_score,nextTetromino);
        while(!quit)
        {
            if(_matrix.hasTetrominoHitBottom(_tetromino,_tetrominoPosition))
            {
                _matrix.addTetrominoToHeap(_tetromino,_tetrominoPosition);
                unsigned noOfRowsDeleted = _matrix.deletePackedRows();
                _score += noOfRowsDeleted;
                _tetrominoPosition = Position(1,4);
                _tetromino = nextTetromino;
                addTetromino();
                nextTetromino = generateRandomTertomino();
                tetrisPainter.drawPanel(_score,nextTetromino);
                _music.playSound(Sound::FORCE_HIT);
                if(noOfRowsDeleted > 0)
                {
                    _music.playSound(Sound::LINE_REMOVAL);
                }
            }

            if(_matrix.hasTetrominoHitHeap(_tetromino,_tetrominoPosition))
            {
                _matrix.addTetrominoToHeap(_tetromino,_tetrominoPosition);
                unsigned noOfRowsDeleted = _matrix.deletePackedRows();
                _score += noOfRowsDeleted;
                _tetrominoPosition = Position(1,4);
                _tetromino = nextTetromino;
                addTetromino();
                nextTetromino = generateRandomTertomino();
                tetrisPainter.drawPanel(_score,nextTetromino);
                _music.playSound(Sound::FORCE_HIT);
                if(noOfRowsDeleted > 0)
                {
                    _music.playSound(Sound::LINE_REMOVAL);
                }
            }
//            std::cout << "SCORE: " << _score << std::endl;
/*
            pauseTime(300);                                 
            _tetrominoPosition._row++;
*/
            while(SDL_PollEvent(&event) != 0)
            {
                switch(event.type)
                {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                    case SDL_QUIT:
                        quit = true; break;
                    case SDLK_UP:
                        moveTetromino(Tetromino::Action::ROTATE);
                        _music.playSound(Sound::ROTATE);
                        break;
                    case SDLK_LEFT:
                        moveTetromino(Tetromino::Action::MOVE_LEFT);
                        break;
                    case SDLK_RIGHT:
                        moveTetromino(Tetromino::Action::MOVE_RIGHT);
                        break;
                    case SDLK_DOWN:
                        moveTetromino(Tetromino::Action::MOVE_DOWN);
                    }
                    break;
                }

                if(SDL_QUIT == event.type)
                {
                    quit = true;
                }
            }
        }
    }

    void Tetris::exit()
    {
        SDL_DestroyWindow(_window);
        _music.exit();
        TTF_Quit();
        SDL_Quit();  
    }

    Tetromino Tetris::generateRandomTertomino() const
    {
        size_t tetrominoShapeIndex = rand() % NO_OF_TETROMINO_SHAPES;
        unsigned red = rand()%255;
        unsigned green = rand()%255;
        unsigned blue = rand()%255;

        return Tetromino(static_cast<Tetromino::Shape>(tetrominoShapeIndex),Color(red,green,blue));
    }
    
    void Tetris::addTetromino()
    {
        _matrix.addTetromino(_tetromino,_tetrominoPosition);
        TetrisPainter tetrisPainter(_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
        tetrisPainter.drawMatrix(_matrix);
    }

    void Tetris::moveTetromino(Tetromino::Action action_)
    {
        //Calculate new position of tetromino based on action
        switch(action_)
        {
        case Tetromino::Action::ROTATE:
            if(_matrix.isTetrominoMovable(_tetromino,
                                          Tetromino::Action::ROTATE,
                                          _tetrominoPosition))
            {
                _matrix.deleteTetrmino(_tetromino,_tetrominoPosition);
                _tetromino.rotate();
                addTetromino();
            }
            break;
        case Tetromino::Action::MOVE_LEFT:
            if(_matrix.isTetrominoMovable(_tetromino,
                                          Tetromino::Action::MOVE_LEFT,
                                          _tetrominoPosition))
            {
                _matrix.deleteTetrmino(_tetromino,_tetrominoPosition);
                _tetrominoPosition._column--;
                addTetromino();
            }
            break;
        case Tetromino::Action::MOVE_RIGHT:
            if(_matrix.isTetrominoMovable(_tetromino,
                                          Tetromino::Action::MOVE_RIGHT,
                                          _tetrominoPosition))
            {
                _matrix.deleteTetrmino(_tetromino,_tetrominoPosition);
                _tetrominoPosition._column++;
                addTetromino();
            }
            break;
        case Tetromino::Action::MOVE_DOWN:
            if(_matrix.isTetrominoMovable(_tetromino,
                                          Tetromino::Action::MOVE_DOWN,
                                          _tetrominoPosition))
            {
                _matrix.deleteTetrmino(_tetromino,_tetrominoPosition);
                _tetrominoPosition._row++;
                addTetromino();
            }
        }
    }
}
