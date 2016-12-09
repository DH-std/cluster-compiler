#!/usr/bin/env python
# encoding: utf-8


from Bio import Phylo
import os
import sys
import pickle


def readFuncName():
    fn = os.path.join(os.path.dirname(__file__), "../output/ncd.phylip")
    f = open(fn, 'r')
    f.readline()
    functionName = []
    for line in f:
        elements = line.split()
        print elements
        functionName.append(elements[0])
    f.close()
    return functionName


def readTree():
    treeFile = os.path.join(os.path.dirname(__file__), "../output/tree.newick")
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


def sort():
    fn = os.path.join(os.path.dirname(__file__), "../output/ncd.phylip")
    f = open(fn, 'r')
    functionNum = int(f.readline())
    functionName = []
    ncdVal = []
    matrix = {}
    for line in f:
        elements = line.split()
        functionName.append(elements[0])
        ncdVal.append(elements[1:])
    for i in range(functionNum):
        sequence = []
        for j in range(functionNum):
            sequence.append([functionName[j], float(ncdVal[i][j])])
        matrix[functionName[i]] = sequence
    f.close()

    # sort
    for key, value in matrix.iteritems():
        matrix[key] = sorted(value, key=lambda ncd: ncd[1])[1:]

    return matrix


def merge(source, funcInSameCluster):
    fn = os.path.join(os.path.dirname(__file__), "../pass/all/ref_pass.pkl")
    funcToPass = pickle.load(open(fn,"rb"))
    passes = []
    for func in funcInSameCluster:
        funcPasses = funcToPass[func]
        for eachPass in funcPasses:
            if eachPass not in passes:
                passes.append(eachPass)

    return passes


if __name__ == '__main__':
    source = sys.argv[1]
    tree = readTree()
    functionName = readFuncName()
    similarFunc = getSimilarFunc(functionName, source, tree)
    passes = merge(source, similarFunc)
    fn = os.path.join(os.path.dirname(__file__),
                      "../output/reduced_space/" + source)
    pickle.dump(passes, open(fn, 'wb'))
