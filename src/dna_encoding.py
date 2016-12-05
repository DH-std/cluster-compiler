import re, os, shutil
import os

def split_again(words):
    ans = []
    word = ""
    i = 0
    while i < len(words):
        if words[i].isalpha() or (words[i] == '_') or words[i].isdigit() or ((words[i] == '*') and (i+1 < len(words) and words[i+1].isalpha())):
            word += words[i]
        else:
            if len(word) > 0:
                ans.append(word)
            test = words[i]
            if i+1 < len(words):
                test = test + words[i+1]
            if (test == '+=' or test == '++' or test == '>=' or test == '<=' or test == '!=' or test == '<<' or test == '>>' or test == "//" or test == "/*" or test =='*/'):
                ans.append(test)
                i = i + 1
            else:
                ans.append(words[i])
            word = ""
        i = i + 1
    return ans


def encode_source_file(filename):
    found_beginning = False
    function_name = filename.split('/')[4].rstrip('.c')
    print "****************: ", function_name
    dna = ""
    real_content = False
    with open(filename) as f:
        for line in f:
            li = line.strip()
            if not li.startswith("/*") and not re.match(r'^\s*$', li):
                print "---------------------------------------------------"
                print li
                # if '(' in li and ')' in li:
                #     print li
                if function_name in li:
                    found_beginning = True
                if ((')' in li and not '(' in li) or ('(' in li and ')' in li and function_name in li)) and found_beginning and not real_content:
                    real_content = True

                if real_content:
                    wl = li.split(' ')
                    rwl = []

                    for ws in wl:
                        ws = ws.strip(';').strip(',').strip('(').strip(')').strip('{').strip('}')
                        if re.match('^[a-zA-Z0-9_.-]*$', ws) or len(ws) <= 1:
                            rwl = rwl + [ws]
                        else:
                            rwl = rwl + split_again(ws)

                    print rwl
                    for w in rwl:
                    # w = w.strip(';').strip('(').strip(')').strip('{').strip('}')
                        if w == "/*" or w == "//":
                            break
                        if len(w) > 0:
                            if re.match('for|while', w):
                                dna += 'H'
                            elif (w == '='):
                                dna += 'E'
                            elif (w == '+='):
                                dna += 'P'
                            elif w == '0':
                                dna += 'Z'
                            elif w == '++':
                                dna += 'Q'
                            elif w == '+' or w == '*':
                                dna += 'A'
                            elif re.match('>|<|>=|<=|==|!=', w) and w != "<<" and w != ">>":
                                dna += 'C'
                            elif "read" in w:
                                dna += 'R'
                            elif "write" in w:
                                dna += 'W'
                            elif w == '[':
                                c = ''
                                if '=' in rwl:
                                    c = '='
                                elif '+=' in rwl:
                                    c = '+='
                                if len(c)>0:
                                    # it is a read if array access is on the right of =,
                                    # otherwise it is a write
                                    if rwl.index(c) < rwl.index('['):
                                        dna = dna.rstrip('I')
                                        dna += 'R'
                                    else:
                                        dna = dna.rstrip('I')
                                        dna += 'W'
                            elif re.match('^[a-zA-Z0-9_.-]*$', w) and not re.match('if|else|int|short|unsigned|char|const|long', w) and not w[0].isdigit():
                                dna += 'I'
                print dna

    return dna

def main():

    # print split_again('i20=in[i+2*w]');
    # print re.match('^[a-zA-Z0-9_.-]*$', 'y[2*i+1]')

    filenames = os.listdir('../benchmark/dsplib/splitted')
    tmp_dir = '../benchmark/dsplib/dna/'

    if os.path.isdir(tmp_dir):
        shutil.rmtree(tmp_dir)
    os.mkdir(tmp_dir)

    for filename in filenames:
        ans = encode_source_file(os.path.join('../benchmark/dsplib/splitted', filename))
        dna_file = open(tmp_dir + filename, 'w')
        dna_file.write(ans)
        dna_file.close()


    filenames = os.listdir('../benchmark/imglib/splitted')
    tmp_dir = '../benchmark/imglib/dna/'

    if os.path.isdir(tmp_dir):
        shutil.rmtree(tmp_dir)
    os.mkdir(tmp_dir)

    for filename in filenames:
        ans = encode_source_file(os.path.join('../benchmark/imglib/splitted', filename))
        dna_file = open(tmp_dir + filename, 'w')
        dna_file.write(ans)
        dna_file.close()



if __name__ == "__main__":
  main()
