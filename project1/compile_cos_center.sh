#!/bin/bash
echo "----------compile this baby--------------"
g++ main.cc -o main.out include/cos_center_difference.hh src/cos_center_difference.cc
echo "--------------------execute this puppy--------------------"
./main.out
echo "------------------------copy output to root folder:--------------------"
cp cos_center_0.1.dat ../root/macros/
ls ../root/macros -l



