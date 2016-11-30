import re, os, shutil
import os

# TODO: implement this
def seperate_functions():
    pass

def encode_source_file(filename):
    count = 0;
    function_name = ""
    dna = ""
    real_content = False
    with open(filename) as f:
        for line in f:
            li = line.strip()
            if not li.startswith("/*") and not re.match(r'^\s*$', li):
                # print li
                if (count == 0):
                    function_name = li.split(' ')[1]
                elif ')' in li and not real_content:
                    real_content = True

                if real_content and count > 0:
                    wl = li.split(' ')
                    for w in wl:
                        w = w.strip(';').strip('(').strip(')').strip('{').strip('}')
                        if len(w) > 0:
                            if re.match('for|while', w):
                                dna += 'H'
                            elif (w == '='):
                                dna += 'E'
                            elif (w == '+='):
                                dna += 'P'
                            elif w == '0':
                                dna += 'Z'
                            elif '++' in w:
                                if w.startswith('++'):
                                    dna += 'QI'
                                elif w.endswith('++'):
                                    dna += 'IQ'
                            elif w == '+' or w == '*':
                                dna += 'A'
                            elif re.match('>|<|>=|<=|==|!=', w) and w != "<<" and w != ">>":
                                dna += 'C'
                            elif "read" in w:
                                dna += 'R'
                            elif "write" in w:
                                dna += 'W'
                            elif re.match('([A-Za-z0-9\-\_]+)', w) and not re.match('if|else|int|short|unsigned|char|const|long', w) and not w[0].isdigit():
                                dna += 'I'
                            # print w, ' ********** ', dna
                count += 1;

    return dna

def main():
    # function_map = seperate_functions()
    filenames = os.listdir('benchmark/dsplib/splitted')
    tmp_dir = 'benchmark/dsplib/dna/'

    if os.path.isdir(tmp_dir):
        shutil.rmtree(tmp_dir)
    os.mkdir(tmp_dir)

    for filename in filenames:
        ans = encode_source_file(os.path.join('benchmark/dsplib/splitted', filename))
        dna_file = open(tmp_dir + filename, 'w')
        dna_file.write(ans)
        dna_file.close()


    # function_map = seperate_functions()
    filenames = os.listdir('benchmark/imglib/splitted')
    tmp_dir = 'benchmark/imglib/dna/'

    if os.path.isdir(tmp_dir):
        shutil.rmtree(tmp_dir)
    os.mkdir(tmp_dir)

    for filename in filenames:
        ans = encode_source_file(os.path.join('benchmark/imglib/splitted', filename))
        dna_file = open(tmp_dir + filename, 'w')
        dna_file.write(ans)
        dna_file.close()



if __name__ == "__main__":
  main()
