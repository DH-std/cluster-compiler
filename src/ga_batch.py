import pickle
from ga import ga
import time

funcs = ['img_fdct_8x8']
results = {}

for f in funcs:
    start = time.time()
    ga_ret = ga(f)
    end = time.time()
    results[f] = (ga_ret[0], ga_ret[1], end-start)
    print f, ga_ret

output = open('ga_batch.pkl', 'wb')
pickle.dump(results, output)
