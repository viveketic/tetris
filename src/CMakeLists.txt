add_subdirectory(lib)

set(Tetris_SRCS Main.cpp)

add_executable(tetris ${Tetris_SRCS} )
target_link_libraries(tetris
TetrisLib
${SDL2_LIBRARY}
${SDL2_TTF_LIBRARIES}
${SDL2_MIXER_LIBRARY}
)
