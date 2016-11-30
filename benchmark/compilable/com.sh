#!/bin/bash

infile=$1
seq=$2

set -x -e
clang -emit-llvm -o $infile.bc -c $infile/$infile.c

llc $infile.bc -o $infile.s
gcc -I . -o $infile.exe $infile.s $infile/${infile}_d.c $infile/${infile}_c.c support.c
time ./$infile.exe

opt -die -loop-simplify < $infile.bc  > $infile.opt.bc
llc $infile.opt.bc -o $infile.opt.s
gcc -I . -o $infile.opt.exe $infile.opt.s $infile/${infile}_d.c $infile/${infile}_c.c support.c
time ./$infile.opt.exe

