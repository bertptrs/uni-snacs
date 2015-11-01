#!/usr/bin/env python2.7

import matplotlib.pyplot as plt
import os
import re
import sys

def main():
    mapping = {}
    mappingFile = file(sys.argv[1])
    it = 1;

    for line in mappingFile:
        if it == 1:
            it = 2
            continue

        parts = line.split('\t')
        mapping[parts[0]] = parts[1].strip()

    for line in sys.stdin:
        parts = line.split('\t')
        print mapping[parts[0]], parts[1].strip()

if __name__ == "__main__":
    main()
