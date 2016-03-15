#!/bin/sh
mkdir bin
clang++ -std=c++11 -stdlib=libc++ -Iinclude src/main.cpp src/mesh.cpp src/query.cpp -o bin/meshquery