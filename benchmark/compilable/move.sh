#!/bin/bash

files=./*
for f in $files
do
  if [ ${f: -3} != ".sh" -a ${f: -4} != ".cpp" ]; then
    echo "$f"
    cp "$f/${f: 2}.c" "../source_code/"
  fi
done
