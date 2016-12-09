#!/usr/bin/env python
# encoding: utf-8

import os
import pickle, subprocess, fitness, sys

def insert_method(fnc, S, N, initial_seq):
    currSeq = initial_seq
    currFit = fitness.evaluate(fnc, currSeq)
    refFit = currFit
    for i in range(N):
        bestSeq = currSeq[:]
        bestFit = currFit
        for p in S:
            for pos in xrange(0, len(currSeq)+1):
                newSeq = currSeq[:]
                newSeq.insert(pos, p)
                newFit = fitness.evaluate(fnc, newSeq)
                if newFit < bestFit:
                    bestSeq = newSeq[:]
                    bestFit = newFit
            if bestFit < currFit:
                currSeq = bestSeq[:]
                currFIt = bestFit
        if currFit < refFit:
            refFit = currFit
        else:
            break
    return bestSeq, bestFit

def main(argv):

    if len(argv) < 3:
        print "error"
        return 0
    function_name = argv[1]
    search_space = argv[2]
    if search_space == "reduced":
        inputfile = open("../output/reduced_space/" + function_name, 'rb')
        passlist = pickle.load(inputfile)
        inputfile.close()
    elif search_space == "full":
        inputfile = open("full_space.pkl", 'rb')
        passlist = pickle.load(inputfile)
        inputfile.close()

    best_seq, best_fit = insert_method(function_name, passlist, 3, [])

    ans = {"seq": best_seq, "fitness": best_fit}

    outputname = '../output/insertion' + search_space + '/' + function_name + '.pkl'
    outputfile = open(outputname, 'wb')
    pickle.dump(ans, outputfile)
    outputfile.close()


if __name__ == "__main__":
    main(sys.argv)
