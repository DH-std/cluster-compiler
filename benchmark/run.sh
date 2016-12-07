#!/bin/bash

files=./complete/*

for f in $files
do
  if [ ${f: 11: 3} = "img" ]; then
    echo "Processing $f"
    mv $f "${f/img/IMG}"
  fi
done
echo "complete"

