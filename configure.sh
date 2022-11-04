#!/bin/bash

MULTIARCH=`gcc -dumpmachine`

for dir in *module; do
    sed -i -e "s/x86_64-linux-gnu/${MULTIARCH}/g" $dir/Makefile
done
