#!/bin/bash
echo "----------compile--------------"
g++ problem3.cc -o prob3.out 
echo "--------------------execute--------------------"
./prob3.out
echo "------------------------copy output to root folder--------------------"
cp output3.dat ../../root/macros/
ls -l ../../root/macros



