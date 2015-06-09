#!/bin/bash

rm $1 -rf 2> /dev/null
mkdir $1
echo $1.mp4 > $1/filename
echo $2 > $1/url
touch $1/$1.srt
