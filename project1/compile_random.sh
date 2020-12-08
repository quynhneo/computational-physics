#!/bin/bash
g++ -o rand.o main_random.cc include/random_include.hh src/random_src.cc
./rand.o
cp sigma2.dat ../root/macros/
ls -l ../root/macros/*.dat
