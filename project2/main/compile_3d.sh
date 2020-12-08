#!/bin/bash
echo "----------compile--------------"
rm prob3d.out
g++ problem3d.cc -o prob3d.out 
echo "--------------------execute--------------------"
./prob3d.out
echo "------------------------copy output to root folder--------------------"
cp output3d.dat ../../root/macros/
ls -l ../../root/macros



