#!/bin/bash

rm tmp -rf 2> /dev/null
mkdir -p tmp/$1
cp rer-files/working/$1/filename tmp/$1
cp rer-files/working/$1/url tmp/$1
cp rer-files/working/$1/$1.srt tmp/$1

cd tmp && zip -r $1.rer $1 > /dev/null; cd ..
mv tmp/$1.rer rer-files/.
rm tmp -rf 2> /dev/null

