#!/bin/bash
python dna_encoding.py $1
python damicore.py ../output/dna_one_function --ncd-output ../output/ncd.phylip --format phylip --tree-output ../output/tree.newick --output ../output/cluster.clusters --compressor bzip2
python ambiguity.py $1
echo "ga"
python random_sample.py $1 reduced
echo "insertion full"
python insertion.py $1 full
echo "insertion reduced"
python insertion.py $1 reduced
echo "clean reduced"
python cleaning_algo.py $1 reduced
echo "clean-insertion"
python clean_insertion.py $1
echo "insertion-clean"
python insertion_cleaning.py $1
echo "finished"
rm ./*.pyc
rm -r ./tmp
rm ./*.s
rm ./*.bc
rm ./*.exe
