#!/bin/bash

if [ ! -d "$1" ]; then
	if [ ! -f "$1.rer" ]; then
		echo "can't find $1!"
	else
		unzip $1.rer > /dev/null
	fi
fi
if [ -d "$1" ]; then
	if [ ! -f "$1/$1.mp4" ]; then
		./dl.sh $1
	fi
fi

