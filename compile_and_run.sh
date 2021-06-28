#!/bin/sh


#source ~/repos/useful-stuff/dotfiles/bashaliases.sh

export DISPLAY=:0       # needed on WSL

echo "----------------------------------------"
echo "deleting old files:"
echo "  "
rm writefile > /dev/null 2>&1

echo "----------------------------------------"
echo "compiling:"
echo "  "
#g++ main.cpp -o writefile 

# Compile with armadillo:
g++ -Wall main.cpp -o writefile -std=c++17 -O2 \
    -static-libstdc++ \
    -larmadillo \
    -lsfml-graphics -lsfml-window -lsfml-system \
    -lglut -lGLU -lGL


# # Compile for windows: does NOT work 
# x86_64-w64-mingw32-gcc main.cpp -o writefile.exe -std=c++17 -O2 \
#     -larmadillo \
#     -lsfml-graphics -lsfml-window -lsfml-system \
#     -lglut -lGLU -lGL


# compile with Eigen:
# g++ main.cpp -o writefile -std=c++11 -O2 \
#      -I /usr/include/eigen3/ \
#      -lsfml-graphics -lsfml-window -lsfml-system \
#      -lglut -lGLU -lGL


#g++ main.cpp -o writefile
echo "----------------------------------------"
echo "output:"
echo "  "
./writefile 

# plot in python:
#python3 plot.py
#python3 animate.py
