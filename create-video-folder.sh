#!/bin/bash

rm rer-files/working/$1 -rf 2> /dev/null
mkdir rer-files/working/$1 -p
echo $1.mp4 > rer-files/working/$1/filename
echo $2 > rer-files/working/$1/url
touch rer-files/working/$1/$1.srt
