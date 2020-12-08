#!/bin/bash
echo "----------compile--------------"
rm prob2.out
g++ problem2.cc -o prob2.out 
echo "--------------------execute--------------------"
./prob2.out
echo "------------------------copy output to root folder--------------------"
cp output2.dat ../../root/macros/
ls -l ../../root/macros



