import os, pickle

def main():
    ans = []
    with open('../pass.txt', 'rb') as f:
        for line in f:
            li = line.strip()
            ans.append(li)
    outputname = 'full_space.pkl'
    outputfile = open(outputname, 'wb')
    pickle.dump(ans, outputfile)
    outputfile.close()

if __name__ == "__main__":
    main()