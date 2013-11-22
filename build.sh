#!/usr/bin/env bash

# Who needs make files?
g++ -I`pwd`/src -std=c++11 -o main `find . -name "*.cpp"` -lSDL2
