Quynh Nguyen
N13331849

bash script To test run all code in linux from this folder. at this folder ROOTSYS is ../root/
these script will run C++ code and copy output file to ../root/macros/
then use go to ../root/ to run macros to plot

example
sh [problemname.sh]
cd ../root/
root
[]: .L problemname.C
[]: graph() or plot()

directory
bash file       and   ROOT file

problem 1

compile_cos_forward.sh  and cos_forward.C
compile_cos_center.sh  and cos_center_diff.C
compile_cos_extrapolation.sh and cos_extrapolation_root.C

compile_exp_forward.sh  and exo_forward.C  
compile_exp_center.sh and exo_center.C  
compile_exp_extrapolation.sh and exp_extrapolation_root.C



problem 2

compile_simpson.sh  and integral_simpson_root.C
compile_traped.sh and integral_trapezoid_root.C

compile_gaussian.sh  and integral_gaussian_root.C


problem 3
compile_random.sh and sigma2.C
