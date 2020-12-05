#!/bin/bash
echo "----------compile--------------"
g++ main.cc -o main.out include/exp_center_difference.hh src/exp_center_difference.cc
echo "--------------------execute--------------------"
./main.out
echo "------------------------copy output to root folder--------------------"
cp exp_center_10.dat ../root/macros/
ls ../root/macros -l



