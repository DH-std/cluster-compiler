import os
import subprocess

def evaluate(fnc, passlist):
    score = 0
    while (score == 0):
        FNULL = open(os.devnull, 'w')
        args = ["./com.sh", fnc] + passlist
        out = subprocess.call(args, stdout=FNULL, stderr=subprocess.STDOUT)
        f = open(os.path.join(os.path.dirname(__file__),"time.output"), 'rb')
        score = int(f.readline())

    # For debug usage, can tell which passes are used and its score
    #print "*************** ", args
    #print "************** SCORE:", score
    # Can comment out above part

    f.close()
    FNULL.close()
    return score
