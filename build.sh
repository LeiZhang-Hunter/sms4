#!/bin/bash

if [ ! -f "build" ]; then
 touch "build"
fi

cd build

cmake ..

make