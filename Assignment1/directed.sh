#!/bin/bash

if [[ $# -lt 1 ]]
then
	echo "No input files provided."
	exit 1
fi

for file in "$@"
do
	echo -n "$file: "
	tmpfile=$(mktemp)
	awk '{if($2 < $1) print $2,$1;else print $1,$2}' "$file" | sort -S 10% --compress-program gzip | gzip > $tmpfile

	edges=$(gzip -cd $tmpfile | wc -l)
	uniqueEdges=$(gzip -cd $tmpfile | uniq | wc -l)

	rm $tmpfile

	if [[ $edges -eq $(expr "$uniqueEdges * 2") ]]; then
		echo "undirected"
	elif [[ $edges -eq $uniqueEdges ]]; then
		echo "possibly undirected"
	else
		echo "directed"
	fi

done
