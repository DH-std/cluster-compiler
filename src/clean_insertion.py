#!/usr/bin/env python
# encoding: utf-8


import os
import pickle
import sys
import cleaning_algo
import insertion


def clean_insertion(passes, functionName):
    fn = os.path.join(os.path.dirname(__file__), "./")
    inputFile = open(fn + "full_space.pkl", 'rb')
    fullSpace = pickle.load(inputFile)
    inputFile.close()
    midSeq, midFit = cleaning_algo.clean_method(functionName, passes)
    bestSeq, bestFit = insertion.insert_method(functionName,
                                               fullSpace,
                                               3,
                                               midSeq)
    return bestSeq, bestFit


if __name__ == "__main__":
    functionName = sys.argv[1]
    fn = os.path.join(os.path.dirname(__file__), "../output/reduced_space/")
    inputFile = open(fn + functionName, 'rb')
    passes = pickle.load(inputFile)
    inputFile.close()
    bestSeq, bestFit = clean_insertion(passes, functionName)
    ans = {"seq": bestSeq, "fitness": bestFit}
    fn = os.path.join(os.path.dirname(__file__), "../output/clean-insertion/")
    outputFile = open(fn + functionName, 'wb')
    pickle.dump(ans, outputFile)
    outputFile.close()
