#!/bin/bash

python src/damicore.py examples --ncd-output output/ncd.csv --format csv --output output/dna.clusters --compressor bzip2
python src/sortReferenceFunctions.py
rm src/*.pyc
rm -r src/tmp
