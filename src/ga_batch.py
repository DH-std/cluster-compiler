import pickle
from ga import ga

funcs = ['img_boundary']
results = {}

for f in funcs:
    results[f] = ga(f)

output = open('ga_batch.pkl', 'wb')
pickle.dump(results, output)
