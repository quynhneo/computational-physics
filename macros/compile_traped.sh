#!/bash/bin
rm inte.o
g++ -o inte.o main_integral.cc include/integral_trapezoid_include.hh src/integral_trapezoid_src.cc
./inte.o
