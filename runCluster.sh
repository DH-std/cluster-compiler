#!/bin/bash

python src/damicore.py examples --ncd-output output/ncd.phylip --format phylip --output output/dna.clusters --compressor bzip2
python src/sortReferenceFunctions.py boundary.c sobel.c pix_sat.c
rm src/*.pyc
rm -r src/tmp
