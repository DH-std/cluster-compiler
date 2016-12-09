import re, os, shutil
import sys

def split_again(words):
    ans = []
    word = ""
    i = 0
    while i < len(words):
        if words[i].isalpha() or (words[i] == '_') or words[i].isdigit() or ((words[i] == '*') and (i+1 < len(words) and words[i+1].isalpha()) and ((i==0) or (i>0)and(not words[i-1].isalpha() and not words[i-1].isdigit()))):
            word += words[i]
        else:
            if len(word) > 0:
                ans.append(word)
            test = words[i]
            if i+1 < len(words):
                test = test + words[i+1]
            if (test == '+=' or test == '++' or test == '>=' or test == '<=' or test == '!=' or test == '<<' or test == '>>' or test == "//" or test == "/*" or test =='*/' or test == '->'):
                ans.append(test)
                i = i + 1
            else:
                ans.append(words[i])
            word = ""
        i = i + 1
    if len(word) > 0:
        ans.append(word)
    return ans


def encode_source_file(filename):
    found_beginning = False
    function_name = filename.split('/')[3].rstrip('.c')
    print function_name
    print "****************: ", function_name
    dna = ""
    real_content = False
    with open(filename) as f:
        for line in f:
            li = line.strip()
            if not li.startswith("/*") and not re.match(r'^\s*$', li):
                # print "---------------------------------------------------"
                # print li
                # if '(' in li and ')' in li:
                #     print li
                if ("IMG_" in li or "DSP_" in li) and not "include" in li and not ";" in li and not found_beginning:
                    found_beginning = True
                    print li
                    continue
                if (')' in li ) and found_beginning and not real_content:
                    real_content = True
                    print li

                if real_content:
                    wl = li.split(' ')
                    rwl = []

                    for ws in wl:
                        ws = ws.strip(';').strip(',').strip('(').strip(')').strip('{').strip('}')
                        if re.match('^[a-zA-Z0-9_.-]*$', ws) or len(ws) <= 1:
                            rwl = rwl + [ws]
                        else:
                            rwl = rwl + split_again(ws)

                    # print rwl
                    for index,w in enumerate(rwl):
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
                                    # print '=============', c, rwl.index(c), rwl.index
                                    if rwl.index(c) < index:
                                        dna = dna.rstrip('I')
                                        dna += 'R'
                                    else:
                                        dna = dna.rstrip('I')
                                        dna += 'W'
                            elif re.match('^[a-zA-Z0-9_.-/*]*$', w) and not re.match('if|else|int|short|signed|unsigned|char|const|long', w) and not w[0].isdigit():
                                dna += 'I'
                # print dna

    return dna

def main(argv):
    tmp_dir = '../output/dna/'

    if len(argv) > 1:
        dna_folder = '../output/dna_one_function/'

        if os.path.isdir(dna_folder):
            shutil.rmtree(dna_folder)
        os.mkdir(dna_folder)

        filename = argv[1] + ".c"

        if not os.path.isfile(os.path.join('../benchmark/source_code/', filename)):
            print filenames[0], "not exists"
            exit(1)

        ans = encode_source_file(os.path.join('../benchmark/source_code', filename))
        dna_file = open(dna_folder + filename[0:-2], 'w')
        dna_file.write(ans)
        dna_file.close()

        files = ['adpcm_coder' , 'adpcm_decoder', 'dsp_autocor', 'bubble_sort', 'dsp_dotprod', 'img_fdct_8x8', 'fibonacci', 'dsp_maxval', 'dsp_minval', 'pop_count', 'img_sobel']

        for ref_file in files:
            ref_file_fullname = os.path.join(tmp_dir, ref_file)
            if os.path.isfile(ref_file_fullname):
                shutil.copy2(ref_file_fullname, dna_folder)
            else:
                ans = encode_source_file(os.path.join('../benchmark/source_code', ref_file+'.c'))
                dna_file = open(tmp_dir + ref_file, 'w')
                dna_file.write(ans)
                dna_file.close()
                shutil.copy2(ref_file_fullname, dna_folder)

    else:
        if os.path.isdir(tmp_dir):
            shutil.rmtree(tmp_dir)
        os.mkdir(tmp_dir)
        filenames = os.listdir('../benchmark/source_code')

        for filename in filenames:
            if ".c" in filename:
                ans = encode_source_file(os.path.join('../benchmark/source_code', filename))
                dna_file = open(tmp_dir + filename[0:-2], 'w')
                dna_file.write(ans)
                dna_file.close()

    # print split_again('i_data[(i');
    # print re.match('^[a-zA-Z0-9_.-]*$', 'y[2*i+1]')


if __name__ == "__main__":
  main(sys.argv)
