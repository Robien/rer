#!/bin/bash

if [ ! -f "prout" ]; then
	echo "prout not found !"
	echo "I will try to build it"
	cd src && g++ -std=c++11 main.cpp -O3 -o prout && mv prout ..; cd ..
	echo "done."
fi

#make the file
./prefetch-all.sh $1
mkdir -p out
rm out/* 2> /dev/null
touch out/cmd
awk 'NR % 2 == 1' $1 | sort | uniq | xargs -L 1 ./catSrt.sh >> out/cmd
cat utils/startcaca $1 >> out/cmd
cat out/cmd | ./prout > cut.sh && chmod +x cut.sh && ./cut.sh
rm cut.sh 2> /bin/bash
