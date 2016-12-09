import pickle
from ga import ga
import time

funcs = ['img_wave_horz', 'img_wave_vert', 'img_sad_8x8', 'img_sad_16x16']

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
