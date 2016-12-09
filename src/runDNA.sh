#!/bin/bash
python dna_encoding.py $1
python damicore.py ../output/dna_one_function --ncd-output ../output/ncd.phylip --format phylip --tree-output ../output/tree.newick --output ../output/cluster.clusters --compressor bzip2
python ambiguity.py $1
python insertion.py $1 $2
python cleaning_algo.py $1 $2
rm ./*.pyc
rm -r ./tmp
