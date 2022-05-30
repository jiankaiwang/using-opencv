#!/bin/bash

rm -rf ./*.jpg
rm -rf ./*.avi
rm -rf ./build
mkdir ./build

cd ./build
cmake ..
cmake --build .

./main

cd ..
