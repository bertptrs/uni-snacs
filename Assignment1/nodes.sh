#!/bin/bash

if [[ $# -lt 1 ]]
then
	echo "No input files provided."
	exit 1
fi

for file in "$@"
do
	echo -n "$file: "

	awk '{print $1;print $2}' "$file" | sort -u | wc -l
done
