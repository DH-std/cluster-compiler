import pickle
from ga import ga
import time

funcs = ['img_yc_demux_le16', 'dsp_blk_eswap64', 'dsp_blk_eswap32']

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
