#!/usr/bin/env python
# encoding: utf-8

from Bio import Phylo
from ete2 import Tree
import networkx as nx
from networkx.drawing.nx_agraph import graphviz_layout


tree = Phylo.read('dnaTree.newick', 'newick')
nx.draw_graphviz(tree)
