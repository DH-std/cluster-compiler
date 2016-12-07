import glob
import pickle
from fitness import evaluate

lst = glob.glob("*.pkl")

xs = []
ys = []
for i in lst:
	data = pickle.load(open(i,'rb'))
	speedup = 1.0 * evaluate(i[:-4], []) / data[i[:-4][1]]
	print  "%s, %.4f" % (i[:-4], speedup)
