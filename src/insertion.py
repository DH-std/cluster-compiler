#!/usr/bin/env python
# encoding: utf-8


def main():
    currSeq = []
    currFit = evaluate(F, currSeq)
    refFit = currFit
    for i in xrange(1, N + 1):
        bestSeq = currSeq
        bestFit = currFit
        for e in xrange(1, len(S)):
            for pos in xrange(0, size(currSeq)):
                newSeq = currSeq
                newSeq.insert(pos, S[e])
                newFit = evaluate(F, newSeq)
                if newFit < bestFit:
                    bestSeq = newSeq
                    bestFit = newFit
            if bestFit < currFit:
                currSeq = bestSeq
                currFIt = bestFit
        if currFit < refFit:
            refFit = currFit
        else:
            break
    return bestSeq

if __name__ == "__main__":
    main()
