import re, os, shutil
import os



def main():
    function_name = 'boundary.c'
    initial_pass_seq = ['a', 'b', 'c']
    clean_method(function_name, initial_pass_seq)

if __name__ == "__main__":
  main()