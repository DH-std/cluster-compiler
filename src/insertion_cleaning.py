import pickle, subprocess, fitness, sys, os
import cleaning_algo, insertion

def insertion_clean_method(fnc):

    inputfile = open("../output/reduced_space/" + fnc, 'rb')
    reduced_space = pickle.load(inputfile)
    inputfile.close()

    inputfile = open("full_space.pkl", 'rb')
    full_space = pickle.load(inputfile)
    inputfile.close()

    mid_seq, mid_fit = insertion.insert_method(fnc, full_space, 1, reduced_space)

    best_seq, best_fit = cleaning_algo.clean_method(fnc, mid_seq)
    return best_seq, best_fit


def main(argv):
    if len(argv) < 2:
        print "error"
        return 0
    function_name = argv[1]

    best_seq, best_fit = insertion_clean_method(function_name)

    ans = {"seq": best_seq, "fitness": best_fit}

    outputname = '../output/insertion-clean/' + function_name + '.pkl'
    outputfile = open(outputname, 'wb')
    pickle.dump(ans, outputfile)
    outputfile.close()


if __name__ == "__main__":
    main(sys.argv)
