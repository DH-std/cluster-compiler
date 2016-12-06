import pickle
from ga import ga
import time

funcs = ['bubble_sort', 'dsp_dotprod', 'img_conv_3x3', 'img_dilate_bin', 'img_fdct_8x8', 'img_mad_16x16', 'img_mad_8x8']

for f in funcs:
    results = {}
    start = time.time()
    ga_ret = ga(f)
    end = time.time()
    results[f] = (ga_ret[0], ga_ret[1], end-start)
    print f, ga_ret
    output = open(f+'.pkl', 'wb')
    pickle.dump(results, output)
    output.close()
