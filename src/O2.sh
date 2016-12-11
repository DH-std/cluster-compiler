#!/bin/bash

outfile=$1
if [ -z $1 ]
then
  outfile="O2.output"
fi

tar_dir=../benchmark/compilable
infiles=($(ls $tar_dir))

make() {
  infile=$1
  clang -O2 -emit-llvm -o $infile.opt.bc -c ../benchmark/compilable/$infile/$infile.c
  llc $infile.opt.bc -o $infile.opt.s
  gcc -I . -o $infile.opt.exe $infile.opt.s ../benchmark/compilable/$infile/${infile}_d.c ../benchmark/compilable/$infile/${infile}_c.c support.c
}

set -e
g++ -o avg.exe avg.cpp
echo > $outfile
for f in ${infiles[@]}
do
  if [ ! -d $tar_dir/$f ]
  then
    continue
  fi

  echo "$f ..."
  echo "$f:" >> $outfile
  time (make $f 2>> /dev/null) 2>> $outfile

  rm time.output
  for i in {1..12}
  do
    ./$f.opt.exe > /dev/null
  done
  mv time.output time.input

  ./avg.exe < time.input > time.output
  #echo >> $outfile
  printf "\ncycle: $(cat time.output)\n\n\n" >> $outfile
  #echo >> $outfile
  #echo >> $outfile
done

GREEN='\033[0;32m'
NC='\033[0m'
echo -e "${GREEN}success!${NC}"
echo "output in file $outfile"
