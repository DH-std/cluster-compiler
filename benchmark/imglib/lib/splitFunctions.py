#!/usr/bin/env python
# encoding: utf-8
import re


def main():
    f = open("img64x_c.src", 'r')
    code = None
    isOpen = False
    for line in f:
        result = re.match(r"[\S]+.c\/[\s]+[\d]+[\s]+0[\s]+0[\s]+0[\s]+[\d]+\s+\`", line[:-1])
        if result is not None:
            name = line[:-1].split()[0][:-1]
            code = open("../splitted/" + name, 'w')
            isOpen = True
        else:
            result = re.match(r"\/\*[\s]+End\sof\sfile\:\s+\S+\s+\*\/", line[:-1])
            if isOpen:
                code.write(line)
            if result is not None:
                code.close()
                isOpen = False
    f.close()

if __name__ == "__main__":
    main()
