#!/bin/bash

rm -rf ./*.jpg
rm -rf ./build
mkdir ./build

cd ./build
cmake ..
cmake --build .

./main

cd ..
