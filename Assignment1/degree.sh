#!/bin/bash

degree=out

while getopts "i" opt; do
	case $opt in
		i)
			degree=in
			;;

		\?)
			echo "Invalid option: -$OPTARG" >&2
			exit 1
			;;
	esac
done
shift $((OPTIND-1))

if [[ $# -lt 1 ]]
then
	echo "No input files provided."
	exit 1
fi

if [[ $degree = "in" ]]
then
	awkcmd='{print $2}'
else
	awkcmd='{print $1}'
fi

for file in "$@"; do
	echo "Distribution of ${degree}degree for $file"

	awk "$awkcmd" "$file" |\
		sort -S 10% --compress-program gzip |\
		uniq -c | awk '{print $1}' |\
	   	sort -n | uniq -c
done
