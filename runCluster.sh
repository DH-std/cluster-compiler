#!/bin/bash

files=./benchmark/source_code/*
for f in $files
do
  echo "Processing $f"
  clang -emit-llvm -o $f
done
echo "Complete compiling"
#python src/damicore.py output/dna --ncd-output output/dnaNcd.phylip --format phylip --tree-output output/dnaTree.newick --output output/dna.clusters --compressor bzip2
#python src/damicore.py output/sourceCode --ncd-output output/sourceCodeNcd.phylip --format phylip --tree-output output/sourceCodeTree.newick --output output/sourceCode.clusters --compressor bzip2
#python src/sortReferenceFunctions.py boundary.c sobel.c pix_sat.c
rm src/*.pyc
rm -r src/tmp
