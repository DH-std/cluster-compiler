#!/bin/bash
target=$1
python dna_encoding.py $1
python damicore.py ../output/dna --ncd-output ../output/ncd.phylip --format phylip --tree-output ../output/tree.newick --output ../output/cluster.clusters --compressor bzip2
python ambiguity.py $1
#python src/sortReferenceFunctions.py boundary.c sobel.c pix_sat.c
rm ./*.pyc
rm -r ./tmp
