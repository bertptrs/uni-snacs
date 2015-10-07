#!/usr/bin/env python2.7

from __future__ import print_function
import fileinput
import re
import sys

def userCode(name):
    if name not in userCode.mapping:
        userCode.maxCode = userCode.maxCode + 1
        userCode.mapping[name] = userCode.maxCode

    return userCode.mapping[name]

userCode.maxCode = 0
userCode.mapping = {}


def main():
    usernamePattern = re.compile('@([a-zA-Z0-9_]+)')

    print("Source\tTarget\tTimestamp")

    for line in fileinput.input():
        parts = line.split("\t", 2)
        timestamp = parts[0]
        user = userCode(parts[1].lower())

        for mention in usernamePattern.findall(parts[2]):
            print(str(user) + "\t" + str(userCode(mention.lower())) +  "\t" + timestamp)

    print("Id\tLabel", file=sys.stderr)
    for username,code in userCode.mapping.items():
        print(str(code) + "\t" + username, file=sys.stderr)

if __name__ == "__main__":
    main()
