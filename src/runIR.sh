#!/bin/bash
./ir.sh $1
python damicore.py ../benchmark/IRs --ncd-output ../output/ncd.phylip --format phylip --tree-output ../output/tree.newick --output ../output/cluster.clusters --compressor bzip2
python ambiguity.py $1
python insertion.py $1 $2
python cleaning_algo.py $1 $2
rm ./*.pyc
rm -r ./tmp
