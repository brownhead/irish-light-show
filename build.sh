#!/usr/bin/env bash

# Who needs make files?
g++ -I`pwd`/src -std=c++11 -o irishls `find . -name "*.cpp"` `sdl2-config --libs` -lSDL2_image $*
