#!/bin/bash
echo "----------compile--------------"
g++ main.cc -o main.out include/exp_extrapolation_header.hh src/exp_extrapolation_module.cc
echo "--------------------execute--------------------"
./main.out
echo "------------------------copy output to root folder--------------------"
cp exp_extrapolated_10.dat ../root/macros/
ls ../root/macros -l



