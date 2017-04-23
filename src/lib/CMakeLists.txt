set(TetrisLib_SRCS 
Matrix.cpp
Painter.cpp
Tetris.cpp
Tetromino.cpp
TetrisPainter.cpp
Music.cpp
)

add_library(TetrisLib STATIC ${TetrisLib_SRCS})
target_link_libraries(TetrisLib
${SDL2_LIBRARY}
${SDL2_TTF_LIBRARIES}
)
