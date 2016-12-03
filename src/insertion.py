#!/usr/bin/env python
# encoding: utf-8

import os
import pickle, subprocess, fitness

def insert_method(fnc, S, N):
    currSeq = []
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
    return bestSeq

def main():

    function_name = "img_boundary"
    passlist = ["-loops", "-inline", "-dse"]
    best_ans = insert_method(function_name, passlist, 1)
    print best_ans


if __name__ == "__main__":
    main()
