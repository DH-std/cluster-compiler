#!/bin/bash

python src/damicore.py output/dna --ncd-output output/dnaNcd.phylip --format phylip --tree-output output/dnaTree.newick --output output/dna.clusters --compressor bzip2
python src/damicore.py output/ir --ncd-output output/irNcd.phylip --format phylip --tree-output output/irTree.newick --output output/ir.clusters --compressor bzip2
#python src/sortReferenceFunctions.py boundary.c sobel.c pix_sat.c
rm src/*.pyc
rm -r src/tmp
