#!/bin/bash
target=$1
./ir.sh $1
python damicore.py ../benchmark/IRs --ncd-output ../output/ncd.phylip --format phylip --tree-output ../output/tree.newick --output ../output/cluster.clusters --compressor bzip2
python ambiguity.py $1
#python src/sortReferenceFunctions.py boundary.c sobel.c pix_sat.c
rm ./*.pyc
rm -r ./tmp
