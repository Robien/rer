#!/bin/bash

if [ ! -d "rer-files/working/$1" ]; then
	if [ ! -f "rer-files/$1.rer" ]; then
		echo "can't find $1!"
	else
		unzip rer-files/$1.rer > /dev/null
	fi
fi
if [ -d "rer-files/working/$1" ]; then
	if [ ! -f "rer-files/working/$1/$1.mp4" ]; then
		./dl.sh $1
	fi
fi

