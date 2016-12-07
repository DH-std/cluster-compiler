#!/bin/bash

files=./benchmark/source_code/*
for f in $files
do
  if [ ${f: -2: 2} = ".c" ]; then
    echo "Processing $f"
    clang -emit-llvm -o "./output/ir/${f:24 : -2}.bc" -c $f
  fi
done
