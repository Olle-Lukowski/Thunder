#!/usr/bin/env zsh

clang -nostdlib -static -Isrc/c/include -g -c -o build.o build.c
ld build.o -o build -e __start
