#!/bash/bin
rm integrate.o
g++ -o integrate.o main_integral.cc include/integral_gaussian_include.hh src/integral_gaussian_src.cc
./integrate.o
cp gaussian.dat ../root/macros/
ls -l ../root/macros/*.dat
