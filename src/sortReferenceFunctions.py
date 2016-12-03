#!/usr/bin/env python
# encoding: utf-8
import os
import sys
import pickle


def getSimilarFunc(source):
    fn = os.path.join(os.path.dirname(__file__), "../output/dna.clusters")
    f = open(fn, 'r')
    f.readline()
    functionName = []
    functionCluster = []
    similarFunc = []
    targetCluster = -1
    for line in f:
        elements = line.split()
        functionName.append(elements[0])
        functionCluster.append(int(elements[1]))
        if elements[0] == source:
            targetCluster = int(elements[1])

    for i in range(len(functionName)):
        if functionCluster[i] == targetCluster and functionName[i] != source:
            similarFunc.append(functionName[i])

    f.close()
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
    fn = os.path.join(os.path.dirname(__file__), "../output/sortedFunctions")

    # save
    output = open(fn, 'wb')
    pickle.dump(matrix, output)
    output.close()
    return matrix


def merge(matrix, source, target):
    sequence = matrix[source]
    passes = []
    for ele in sequence:
        if ele[0] in target:
            print ele[0]


def main():
    source = sys.argv[1]
    target = sys.argv[2:]
    matrix = sort()
    merge(matrix, source, target)
    similarFunc = getSimilarFunc(source)
    print similarFunc


if __name__ == "__main__":
    main()
