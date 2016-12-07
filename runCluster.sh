#!/bin/bash

python src/damicore.py benchmark/IRs --ncd-output output/ncd.phylip --format phylip --tree-output output/tree.newick --output output/cluster.clusters --compressor bzip2
#python src/sortReferenceFunctions.py boundary.c sobel.c pix_sat.c
rm src/*.pyc
rm -r src/tmp
