#!/bin/bash

if [ -z $1 ]
then
  echo "usage: $0 test_file <optimization_sequence>"
  exit 1
fi

infile=$1
seq=$2

set -x -e
clang -emit-llvm -o $infile.bc -c $infile/$infile.c
opt $seq < $infile.bc  > $infile.opt.bc
llc $infile.opt.bc -o $infile.opt.s
gcc -I . -o $infile.opt.exe $infile.opt.s $infile/${infile}_d.c $infile/${infile}_c.c support.c
time ./$infile.opt.exe

