import random
import sys
import pickle
from fitness import evaluate


POP_SIZE = 300
def random_sample(passlist, function_name):
	parents = []
	for _ in range(POP_SIZE):
		tmp = []
		size = random.randint(1,len(passlist))
		indexes = random.sample(range(len(passlist)), size)
		for i in indexes:
			tmp.append(passlist[i])
		fit_score = evaluate(function_name, tmp)
		if fit_score == 0:
			fit_score = evaluate(function_name, tmp)
		parents.append((tmp, fit_score))
	parents = sorted(parents, key=lambda x: x[1])
	return parents[0][0], parents[0][1]


def main(argv):
	if len(argv) < 3:
		print "error"
		return 0
	function_name = argv[1]
	search_space = argv[2]
	if search_space == "reduced":
		inputfile = open("../output/reduced_space/" + function_name, 'rb')
		passlist = pickle.load(inputfile)
		inputfile.close()
		best_seq, best_fit = random_sample(passlist, function_name)
		ans = {"seq": best_seq, "fitness": best_fit}
		outputname = '../output/random_sample/' + function_name + '.pkl'
		outputfile = open(outputname, 'wb')
		pickle.dump(ans, outputfile)
		outputfile.close() 
	elif search_space == "full":
		print "no reduced space"
		return 0

if __name__ == "__main__":
	main(sys.argv)
