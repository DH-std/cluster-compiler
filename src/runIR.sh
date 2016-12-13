#!/bin/bash
for file in "dsp_minerror"
do
  ./ir.sh $file
  echo "$file"
  rm "../output/IRtime/$file"
  python damicore.py ../benchmark/IRs --ncd-output ../output/ncd.phylip --format phylip --tree-output ../output/tree.newick --output ../output/cluster.clusters --compressor bzip2
  python ambiguity.py $file
  echo "ga"
  SECONDS=0
  python random_sample.py $file reduced
  duration=$SECONDS
  echo "ga reduced: $duration" >> "../output/time/$file"
  #echo "insertion full"
  #SECONDS=0
  #python insertion.py $file full
  #duration=$SECONDS
  #echo "insertion reduced: $duration" >> "../output/time/$file"
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
  python cic.py $file
  duration=$SECONDS
  echo "clean-insertion: $duration" >> "../output/time/$file"
  echo "insertion-clean"
  SECONDS=0
  python insertion_cleaning.py $file
  duration=$SECONDS
  echo "insertion-clean: $duration" >> "../output/time/$file"
done
rm ./*.pyc
rm -r ./tmp
rm ./*.s
rm ./*.bc
rm ./*.exe
