#!/bin/bash

cd rer-files/working/$1
youtube-dl $(cat url) -o $(cat filename)
cd - > /dev/null
