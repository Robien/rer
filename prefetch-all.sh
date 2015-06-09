#!/bin/bash

awk 'NR % 2 == 1' $1 | sort | uniq | xargs -L 1 ./prepare-video.sh
