#!/usr/bin/env python2.7

import fileinput
import matplotlib.pyplot as plt
import re
import itertools

colors = itertools.cycle(['b', 'g', 'r', 'c', 'm', 'y', 'k'])

def addToPlot(weights, indices, filename, index):
    totalOccurrence = sum(weights)
    normalized = [x / float(totalOccurrence) for x in weights]
    inds = [x + 1/3.0 * index for x in indices]
    plt.bar(inds, normalized, 1/3.0, label=filename, color=colors.next());


def main():
    number = -1

    plt.yscale("log")
    plt.xlabel("Distance")
    plt.ylabel("Relative occurence")

    entryPattern = re.compile('\s*(\d+)\s+(\d+)$')

    for line in fileinput.input():
        m = entryPattern.match(line)
        if m:
            parts = line.split("\t", 2)
            inds.append(int(parts[0]) + 0.5)
            weights.append(int(parts[1]))
        else:
            if number >= 0:
                addToPlot(weights, inds, filename, number)

            number = number + 1
            filename = line.strip()
            inds = []
            weights = []

    addToPlot(weights, inds, filename, number)

    plt.legend()
    plt.savefig("distance-distribution.pdf")

if __name__ == "__main__":
    main()
