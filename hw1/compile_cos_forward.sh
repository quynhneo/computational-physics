#!/bin/bash
echo "----------compile--------------"
g++ main.cc -o main.out include/cos_forward_difference.hh src/cos_forward_difference.cc
echo "--------------------execute--------------------"
./main.out
echo "------------------------copy output to root folder--------------------"
cp cos_forward_10.dat ../root/macros/
ls ../root/macros -l



