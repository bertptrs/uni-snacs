#!/bin/bash

if [[ $# -lt 1 ]]
then
	echo "No input files provided."
	exit 1
fi

for file in "$@"
do
	echo -n "$file: "

	uniqueEdges=$(awk '{if($2 < $1) print $2,$1;else print $1,$2}' "$file" | sort -u -S 10% --compress-program gzip | wc -l)
	edges=$(wc -l < "$file")

	if [[ $edges -eq $(($uniqueEdges * 2)) ]]; then
		echo "undirected"
	elif [[ $edges -eq $uniqueEdges ]]; then
		echo "possibly undirected"
	else
		echo "directed"
	fi

done
