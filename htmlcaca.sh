#!/bin/bash

find rer-files/working/* -name "filename" -exec cat {} \; | xargs -L 1 -i basename {} .mp4 | xargs -L 1 ./catSrt.sh > allsrt.txt && sed -e 's/^/a+=\"/' allsrt.txt > allsrt2.txt &&  sed -e 's/$/\\n\";/' allsrt2.txt > allsrt.txt

cat utils/debut.html allsrt.txt utils/end.html > index.html

rm allsrt.txt allsrt2.txt 2> /dev/null

firefox index.html &




