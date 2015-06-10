#!/bin/bash


if [ ! -d "rer-files" ]; then
	git clone https://github.com/Robien/rer-files.git
fi

cd rer-files
git pull origin master
cd ..
find rer-files/working/* -name "filename" -exec cat {} \; | xargs -L 1 -i basename {} .mp4 | xargs -L 1 ./rerify.sh

