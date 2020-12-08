#!/bin/bash
echo "----------compile--------------"
g++ problem1.cc 
echo "--------------------execute--------------------"
./a.out
echo "------------------------copy output to root folder--------------------"
cp output.dat ../../root/macros/
ls -l ../../root/macros



