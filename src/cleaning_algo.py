import os
import pickle

def evaluate(fnc, passlist):
    

def clean_method(fnc, inputpass):
    best_seq = inputpass
    best_fit = evaluate(fnc, best_seq)
    for p in inputpass:
        new_seq = best_seq
        new_seq.pop(best_seq.index(p))
        new_fit = evaluate(fnc, new_seq)
        if new_fit <= best_fit:
            best_seq = new_seq
            best_fit = new_fit
    return best_seq


def main():
    # fn = os.path.join(os.path.dirname(__file__), "../output/sortedFunctions")
    # print fn
    # f = open(fn, 'rb')
    # dic = pickle.load(f)
    # f.close()
    # print dic

    function_name = "boundary.c"
    inputpass = ["-loops", "-inline", "-dse"]
    best_ans = clean_method(function_name, passlist)


if __name__ == "__main__":
    main()
