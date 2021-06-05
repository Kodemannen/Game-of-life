#!/bin/sh

rm writefile > /dev/null 2>&1
g++ main.cpp -o writefile
./writefile 
