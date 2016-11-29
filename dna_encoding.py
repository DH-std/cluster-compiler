import re

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
                print li
                if (count == 0):
                    function_name = li.split(' ')[1]
                elif li.find(')') and not real_content:
                    real_content = True

                if real_content and count > 0:
                    wl = li.split(' ')
                    for w in wl:
                        if re.search('for|while', w):
                            dna += 'H'
                        # elif ()

                count += 1;

    print dna

def main():
    function_map = seperate_functions()
    encode_source_file("test.c")



if __name__ == "__main__":
  main()
