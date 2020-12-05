#!/bin/bash
echo "----------compile--------------"
g++ problem3_newtonian.cc -o prob3newton.out 
echo "--------------------execute--------------------"
./prob3newton.out
echo "------------------------copy output to root folder--------------------"
cp output3_newton.dat ../../root/macros/
ls -l ../../root/macros



