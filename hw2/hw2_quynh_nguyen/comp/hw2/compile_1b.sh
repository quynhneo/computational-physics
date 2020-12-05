#!/bin/bash
echo "----------compile--------------"
g++ problem1_b_backup.cc 
echo "--------------------execute--------------------"
./a.out
echo "------------------------copy output to root folder--------------------"
cp output1b.dat ../../root/macros/
ls -l ../../root/macros



