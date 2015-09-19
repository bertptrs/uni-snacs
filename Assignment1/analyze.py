#!/usr/bin/env python2.7

import matplotlib.pyplot as plt
import os
import re
import sys

def plot(filename, direction, entries):
    items = list(entries.items())
    items.sort()
    degrees, occurences = zip(*items)

    plt.yscale('log')
    plt.xscale('log')
    plt.xlabel("Degree")
    plt.ylabel("Number of occurences")

    plt.plot(degrees, occurences, label=direction.capitalize() + "degree for " + os.path.basename(filename))

def main():
    direction=None
    filename=None
    entries=None

    headerPattern = re.compile('Distribution of (in|out)degree for (.*)$')
    entryPattern = re.compile('\s*(\d+)(\s+)(\d+)$')

    for line in sys.stdin:
        m = headerPattern.match(line)
        if m:
            if filename:
                plot(filename, direction, entries)

            direction = m.group(1)
            filename = m.group(2)
            entries = {}
        else:
            m = entryPattern.match(line)
            occurence = int(m.group(1))
            degree = int(m.group(3))
            entries[degree] = occurence

    if filename:
        plot(filename, direction, entries)
    else:
        print "No data provided"
        sys.exit(1)

    plt.legend()
    plt.savefig("degree-distributions.pdf")

if __name__ == "__main__":
    main()
