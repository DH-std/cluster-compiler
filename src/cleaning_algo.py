import os
import pickle, subprocess

def evaluate(fnc, passlist):
    args = ["./com.sh", fnc] + passlist
    out = subprocess.call(args)
    f = open("time.output", 'rb')
    score = int(f.readline())
    f.close()
    return score

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

    function_name = "img_boundary"
    passlist = ["-loops", "-inline", "-dse"]
    best_ans = clean_method(function_name, passlist)
    print best_ans


if __name__ == "__main__":
    main()
