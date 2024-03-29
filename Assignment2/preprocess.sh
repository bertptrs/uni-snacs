#!/bin/bash

dir=`dirname $0`

if [ -x $(which pypy) ]; then
	pypy $dir/preprocess.py "$@" 2> /dev/null
else
	$dir/preprocess.py "$@" 2> /dev/null
fi
