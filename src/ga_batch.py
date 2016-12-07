import pickle
from ga import ga
import time

funcs = ['dsp_vecsumsq', 'dsp_w_vec', 'dsp_minerror', 'dsp_maxidx']

for f in funcs:
    results = {}
    start = time.time()
    ga_ret = ga(f)
    end = time.time()
    results[f] = (ga_ret[0], ga_ret[1], end-start)
    print f, ga_ret
    output = open(f + '.pkl', 'wb')
    pickle.dump(results, output)
    output.close()
