import pickle, os

def main():
	filenames = sorted(os.listdir('.'))
	for filename in filenames:
        	if filename != "test" and filename != 'get_fitness.py' and filename != 'img_idct_8x8_12q4':
			inputfile = open('./' + filename, 'rb')
			p = pickle.load(inputfile)
			print filename, p['fitness']
			inputfile.close()

if __name__ == "__main__":
  main()


