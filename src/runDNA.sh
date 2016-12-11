#!/bin/bash

for file in "img_boundary" "img_corr_gen" "img_wave_vert" "img_erode_bin"
do
  echo "$file"
  rm "../output/time/$file"
  python dna_encoding.py $file
  python damicore.py ../output/dna_one_function --ncd-output ../output/ncd.phylip --format phylip --tree-output ../output/tree.newick --output ../output/cluster.clusters --compressor bzip2
  python ambiguity.py $file
  echo "ga"
  SECONDS=0
  python random_sample.py $file reduced
  duration=$SECONDS
  echo "ga reduced: $duration" >> "../output/time/$file"
  echo "insertion full"
  SECONDS=0
  python insertion.py $file full
  duration=$SECONDS
  echo "insertion reduced: $duration" >> "../output/time/$file"
  echo "insertion reduced"
  SECONDS=0
  python insertion.py $file reduced
  duration=$SECONDS
  echo "insert reduced: $duration" >> "../output/time/$file"
  echo "clean reduced"
  SECONDS=0
  python cleaning_algo.py $file reduced
  duration=$SECONDS
  echo "clean reduced: $duration" >> "../output/time/$file"
  echo "clean-insertion"
  SECONDS=0
  python clean_insertion.py $file
  duration=$SECONDS
  echo "clean-insertion: $duration" >> "../output/time/$file"
  echo "insertion-clean"
  SECONDS=0
  python insertion_cleaning.py $file
  duration=$SECONDS
  echo "insertion-clean: $duration" >> "../output/time/$file"
done
echo "finished"
rm ./*.pyc
rm -r ./tmp
rm ./*.s
rm ./*.bc
rm ./*.exe
