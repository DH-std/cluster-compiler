#!/bin/bash

if [ -z $1 ]
then
  echo "usage: $0 test_file <optimization_sequence>"
  exit 1
fi

infile=$1
seq=$2

set -x -e
clang -emit-llvm -o $infile.bc -c ../benchmark/compilable/$infile/$infile.c
opt $seq < $infile.bc  > $infile.opt.bc
llc $infile.opt.bc -o $infile.opt.s
gcc -I . -o $infile.opt.exe $infile.opt.s ../benchmark/compilable/$infile/${infile}_d.c ../benchmark/compilable/$infile/${infile}_c.c support.c

set +x +e
rm time.output

for i in {1..12}
do
  ./$infile.opt.exe
done
mv time.output time.input

set -e
g++ -o avg.exe avg.cpp
./avg.exe < time.input > time.output
cat time.output

set +e
GREEN='\033[0;32m'
NC='\033[0m'
echo -e "${GREEN}success!${NC}"
echo "output in file time.output"

if [ -z $3 ]
then
  rm *.bc
  rm *.s
  rm *.exe
fi
