#!/bin/sh


#source ~/repos/useful-stuff/dotfiles/bashaliases.sh


echo "----------------------------------------"
echo "deleting old files:"
echo "  "
rm writefile > /dev/null 2>&1

echo "----------------------------------------"
echo "compiling:"
echo "  "
g++ main.cpp -o writefile -std=c++11 -O2 -larmadillo

        #
        # -std is what standard library to use,
        # -O2 is the level of optimization
        # -l is library, I guess


#g++ main.cpp -o writefile
echo "----------------------------------------"
echo "output:"
echo "  "
./writefile 

# plot in python:
#python3 animate.py
python3 plot.py
