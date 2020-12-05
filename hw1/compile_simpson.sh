#!/bash/bin
rm integrate.o
g++ -o integrate.o main_integral.cc include/integral_simpson_include.hh src/integral_simpson_src.cc
./integrate.o
cp simpson.dat ../root/macros/
ls -l ../root/macros/*.dat
