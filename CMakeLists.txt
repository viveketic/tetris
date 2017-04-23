cmake_minimum_required(VERSION 2.8)
project (Tetris)

SET(CMAKE_CXX_FLAGS "-lSDL2 -g -lSDL2_ttf -lfreetype -lSDL2_mixer  -std=c++0x -pthread")

include_directories (${CMAKE_SOURCE_DIR}/src/lib)

#include FindSDL2.cmake
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
#set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")


# Look up SDL2 and add the include directory to our include path
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

#This is for ttf font library
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

# This is for SDL2_mixer
find_package(SDL2_Mixer REQUIRED)
include_directories(${SDL2_MIXER_INCLUDE_DIR})


file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/)

add_subdirectory (src)


