#!/usr/bin/env python
# encoding: utf-8
import os
import pickle


def main():
    fn = os.path.join(os.path.dirname(__file__), "../output/ncd.csv")
    f = open(fn, 'r')
    f.readline()
    matrix = {}
    for line in f:
        elements = line.split(',')
        source = elements[0][1:-1]
        target = elements[1][1:-1]
        if source not in matrix:
            matrix[source] = []
        ncd = float(elements[-1])
        tmp = matrix[source]
        tmp.append([target, ncd])
        matrix[source] = tmp
    f.close()

    # sort
    for key, value in matrix.iteritems():
        matrix[key] = sorted(value, key=lambda ncd: ncd[1])
    fn = os.path.join(os.path.dirname(__file__), "../output/sortedFunctions")

    # save
    output = open(fn, 'wb')
    pickle.dump(matrix, output)
    output.close()

if __name__ == "__main__":
    main()
