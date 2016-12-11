com.sh:  
-run in compilable directory  
-./com.sh test_name <"sequence">  
-output will be saved in compilable directory in file time.output

src/fitness.py
- used for calculate fitness scores
- import fitness
- fitness.evaluate(function_name, list_of_passes_including_dash)

Installation
- python 2.7
- easy_install: sudo apt-get install python-setuptools python-dev build-essential 
- pip: sudo easy_install pip 
- make: sudo apt-get install build-essential
- igraph library:
  - Download: http://igraph.org/nightly/get/c/igraph-0.7.1.tar.gz
  - Commands: (may need sudo)
      1. ./configure
      2. make
      3. make check
      4. make install
- python-igraph: (sudo) pip install python-igraph
- Numpy: sudo apt-get install python-numpy
- Bio: sudo easy_install -f http://biopython.org/DIST/ biopython
