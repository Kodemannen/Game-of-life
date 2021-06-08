#!/bin/sh


#source ~/repos/useful-stuff/dotfiles/bashaliases.sh


echo "----------------------------------------"
echo "deleting old files:"
echo "  "
rm writefile > /dev/null 2>&1

echo "----------------------------------------"
echo "compiling:"
echo "  "
#g++ main.cpp -o writefile 
g++ main.cpp -o writefile -std=c++11 -O2 -larmadillo -lsfml-graphics -lsfml-window -lsfml-system


#g++ main.cpp -o writefile
echo "----------------------------------------"
echo "output:"
echo "  "
./writefile 

# plot in python:
#python3 plot.py
#python3 animate.py
