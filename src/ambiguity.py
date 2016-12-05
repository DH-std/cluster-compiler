#!/usr/bin/env python
# encoding: utf-8


from Bio import Phylo
import os
import sys


def readFuncName():
    fn = os.path.join(os.path.dirname(__file__), "../output/ncd.phylip")
    f = open(fn, 'r')
    f.readline()
    functionName = []
    for line in f:
        elements = line.split()
        functionName.append(elements[0])
    f.close()
    return functionName


def readTree():
    treeFile = os.path.join(os.path.dirname(__file__), "../output/texts.newick")
    tree = Phylo.read(treeFile, 'newick')
    return tree


def getSimilarFunc(functionName, source, tree):
    similarFunc = []
    for name in functionName:
        if name != source:
            path = tree.trace(name, source)
            if len(path) <= 4:
                similarFunc.append(name)

    return similarFunc


if __name__ == '__main__':
    source = sys.argv[1]
    tree = readTree()
    functionName = readFuncName()
    similarFunc = getSimilarFunc(functionName, source, tree)
    print similarFunc
