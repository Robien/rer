#!/bin/bash

cd $1
youtube-dl $(cat url) -o $(cat filename)
cd - > /dev/null
