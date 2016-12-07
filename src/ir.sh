#!/bin/bash

dir=../benchmark/IRs
tar_dir=../benchmark/compilable

make() {
  echo "compile IR for $1"
  clang -emit-llvm -o $dir/$1 -c $tar_dir/$1/$1.c
}

if [ ! -d "$dir" ]
then
  mkdir $dir
fi

files=(
  "adpcm_coder" "adpcm_decoder" "dsp_autocor"
  "bubble_sort" "dsp_dotprod"   "img_fdct_8x8"
  "fibonacci"   "dsp_maxval"    "dsp_minval"
  "pop_count"   "img_sobel"
)


rm $dir/*
for infile in ${files[@]}
do
  make $infile
done

echo
if [ -z $1 ]
then
  targets=($(ls $tar_dir))
  for target in ${targets[@]}
  do
    if [ -d "$tar_dir/$target" ]
    then
      make $target
    fi
  done
else
  if [ -d "$tar_dir/$1" ]
  then
    make $1
  else
    echo "$1 does not exits"
  fi
fi
