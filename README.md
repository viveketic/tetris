#Tetris
Classic tetris game in C++ using SDL2.0.

#Build
Make sure you have CMake to build the project. If not, install by

```
sudo apt-get install cmake
```

Make sure you have TTF. IF not, install by
```
sudo apt-get install libsdl-ttf2.0-0
sudo apt-get install libsdl2-ttf-dev   
```

Follow below steps to build the project.
```
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Debug ../
make
```