import pickle, os

def main():

	filenames = os.listdir('.')
	for filename in filenames:
        	if filename != "test" and filename != 'get_fitness.py':
			inputfile = open('./' + filename, 'rb')
			p = pickle.load(inputfile)
			print filename, p['fitness']
			inputfile.close()

if __name__ == "__main__":
  main()


