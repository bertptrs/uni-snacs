#!/bin/bash

for file in "$@"; do
	tmp=$(mktemp)
	./preprocess.sh "$file" | gzip > $tmp
	for degree in "in" "out"; do
		echo "Distribution of ${degree}degree for $file"
		zcat $tmp \
			| ./parser ${degree}degrees \
			| awk '{print $2}' \
			| sort | uniq -c \
			| sort -k 2n
	done
	rm $tmp
done
