#!/bash/bin
rm integrate.o
g++ -o integrate.o main_integral.cc include/integral_trapezoid_include.hh src/integral_trapezoid_src.cc
./integrate.o
cp trapez.dat ../root/macros/
ls -l ../root/macros/*.dat
