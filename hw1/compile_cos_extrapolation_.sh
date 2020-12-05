#!/bin/bash
echo "----------compile--------------"
g++ main.cc -o main.out include/cos_extrapolation_header.hh src/cos_extrapolation_module.cc
echo "--------------------execute--------------------"
./main.out
echo "------------------------copy output to root folder--------------------"
cp cos_extrapolated_0.1.dat ../root/macros/
ls ../root/macros -l



