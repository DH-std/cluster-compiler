# Mitigating the Exploration of Compiler Optimization Sequence Using Clustering-Based Pass Selection in LLVM

### Structure
- `/src` folder contains all implementation and scripts running our system
- `/benchmark` folder includes all reference functions and test functions, and `compilable` subfolder has everything needs to compile those functions
- `/dna_output` and `/ir_output` store our best optimization sequence and its corresponding cycles for each algorithm on different search space.
### Installation
We run our system on AWS ubuntun instance. Following software needs to be installed to run our system:
- python 2.7
- g++ version 5.4 or higher is required.
- easy_install: sudo apt-get install python-setuptools python-dev build-essential
- pip: sudo easy_install pip
- make: sudo apt-get install build-essential
- Additional library:
1. sudo apt-get install libxml2-dev
2. sudo apt-get install libz-dev
- igraph library:
- sudo apt-get install python-igraph
- If the above method failed, download: http://igraph.org/nightly/get/c/igraph-0.7.1.tar.gz
- Commands: (may need sudo)
1. ./configure
2. make
3. make check
4. make install
- python-igraph: (sudo) pip install python-igraph
- Numpy: sudo apt-get install python-numpy
- Bio: sudo easy_install -f http://biopython.org/DIST/ biopython

### Running instructions
##### DNA
Goto `/src`, run DNA based clustering and pass optimization on all DSE algorithms using
```sh
$ ./runDNA.sh
```
You can switch test functions by changing the third line in `runDNA.sh`

##### IR
Goto `/src`, run IR based clustering and pass optimization on all DSE algorithms using
```sh
$ ./runIR.sh
```
You can switch test functions by changing the third line in `runIR.sh`
