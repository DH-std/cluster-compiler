#!/usr/bin/env python
# encoding: utf-8

import requests
import os


def highlight():
    url = 'http://hilite.me/api'
    fn = os.path.join(os.path.dirname(__file__), "../benchmark/imglib/splitted/boundary.c")
    f = open(fn, 'r')
    code = ""
    for line in f:
        code = line
        para = {'code': code, 'lexer': 'c'}
        print code
        r = requests.get(url, params=para)
        print r.text
    f.close()


if __name__ == '__main__':
    highlight()
