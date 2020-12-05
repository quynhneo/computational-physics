#!/bin/bash
echo "----------compile--------------"
rm prob1.out
g++ problem1.cc -lm -lfftw3 -o prob1.out 
echo "--------------------execute--------------------"
./prob1.out
echo "------------------------copy output to root folder--------------------"
cp 1a.dat ../../root/macros/
ls -l ../../root/macros



