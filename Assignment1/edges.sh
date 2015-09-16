#!/bin/bash

for file in "$@"; do
	wc -l "$file"
done
