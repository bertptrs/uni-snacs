#!/usr/bin/env python2.7

from __future__ import print_function
import fileinput
import re
import sys

def userCode(name):
    if name not in userCode.mapping:
        userCode.maxCode = userCode.maxCode + 1
        userCode.mapping[name] = userCode.maxCode
        print(str(userCode.maxCode) + "\t" + name, file=sys.stderr)

    return userCode.mapping[name]

userCode.maxCode = 0
userCode.mapping = {}


def main():
    usernamePattern = re.compile('\W@([a-zA-Z0-9_]{1,15})\W')

    print("Source\tTarget\tTimestamp")
    print("Id\tLabel", file=sys.stderr)

    for line in fileinput.input():
        parts = line.split("\t", 2)
        timestamp = parts[0]
        user = parts[1].lower()

        for mention in usernamePattern.findall(parts[2]):
            if len(mention) > 15:
                continue
            print(str(userCode(user)) + "\t" + str(userCode(mention.lower())) +  "\t" + timestamp)

if __name__ == "__main__":
    main()
