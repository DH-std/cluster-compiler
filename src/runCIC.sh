#!/bin/bash

for file in "dsp_blk_eswap32" "dsp_blk_eswap64" "dsp_blk_move" "dsp_dotp_sqr"
do
  echo "$file"
  python dna_encoding.py $file
  python damicore.py ../output/dna_one_function --ncd-output ../output/ncd.phylip --format phylip --tree-output ../output/tree.newick --output ../output/cluster.clusters --compressor bzip2
  python ambiguity.py $file
  echo "CIC"
  SECONDS=0
  python cic.py $file
  duration=$SECONDS
  echo "CIC: $duration" >> "../output/time/$file"
done
echo "finished"
rm ./*.pyc
rm -r ./tmp
rm ./*.s
rm ./*.bc
rm ./*.exe
