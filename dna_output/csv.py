#!/usr/bin/env python
# encoding: utf-8
import glob
import os
import pickle

output = open("edna.csv",'w') 
results = {}

benchmarks = ["../pass", "clean-insertion", "insertion-clean", "insertionfull", "insertionreduced", "cleanreduced", "random_sample"]

ref_funcs = ['adpcm_coder', 'adpcm_decoder', 'bubble_sort', 'dsp_autocor', 'dsp_dotprod', 'img_fdct_8x8', 'fibonacci', 'dsp_maxval', 'dsp_minval', 'pop_count', 'img_sobel']

for b in benchmarks:
    for i in glob.glob(b+"/*"):
        if os.path.isfile(i):
            try:
                func = os.path.splitext(os.path.basename(i))[0]
                if func in ref_funcs:
                    pass
                else: 
                    p = pickle.load(open(i, 'rb'))
                    if b == "../pass":
                        if func not in results.keys():
                            results[func] = {}
                        results[func][b] =  p[func][1]
                    else:
                        if func not in results.keys():
                            results[func] = {}
                        results[func][b] =  p['fitness']
            except:
                continue

for k, v in results.items():
    diff = set(benchmarks).difference(set(v.keys()))
    if diff:
        print "%s missing for %s" % (list(diff), k)
    else:
        errs = ""
        gaf = v['../pass']
        if gaf == 0:
            errs += "ga error for %s\n" % k 
        ci = v['clean-insertion']
        if ci == 0:
            errs += "ci error for %s\n" % k
        ic = v['insertion-clean']
        if ic == 0:
            errs += "ic error for %s\n" % k
        insrtf = v['insertionfull']
        if insrtf == 0:
            errs += "insrtf error for %s\n" % k
        insrtr = v['insertionreduced']
        if insrtr == 0:
            errs += "insrtr error for %s\n" % k
        cr = v['cleanreduced']
        if cr == 0:
            errs += "cr error for %s\n" % k
        rs = v['random_sample']
        if rs == 0:
            errs += "rs error for %s\n" %k

        if errs:
            print errs
            continue
        else:
            output.write(str(k) + "," + str(gaf) + "," + str(ci) + "," + str(ic) + "," + str(insrtf) + "," + str(insrtr) + "," + str(cr) + "," + str(rs) + "\n")
        
