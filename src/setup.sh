#!/bin/bash

sudo apt-get update
sudo apt-get install llvm
sudo apt-get install clang

sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt install gcc-6
sudo apt install g++-6
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-6 60 --slave /usr/bin/g++ g++ /usr/bin/g++-6
sudo apt install python
sudo apt-get install python-igraph

sudo apt-get install python-setuptools python-dev build-essential
sudo easy_install -f http://biopython.org/DIST/ biopython
