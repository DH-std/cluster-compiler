import os
import pickle, subprocess, fitness, sys

def clean_method(fnc, inputpass):
    best_seq = inputpass[:]
    best_fit = fitness.evaluate(fnc, best_seq)
    for p in inputpass:
        new_seq = best_seq[:]
        new_seq.pop(best_seq.index(p))
        new_fit = fitness.evaluate(fnc, new_seq)
        if new_fit <= best_fit:
            best_seq = new_seq[:]
            best_fit = new_fit
    return best_seq, best_fit


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
        print "no full space"
        return 0

    best_seq, best_fit = clean_method(function_name, passlist)

    ans = {"seq": best_seq, "fitness": best_fit}

    outputname = '../output/clean' + search_space + '/' + function_name + '.pkl'
    outputfile = open(outputname, 'wb')
    pickle.dump(ans, outputfile)
    outputfile.close()


if __name__ == "__main__":
    main(sys.argv)
