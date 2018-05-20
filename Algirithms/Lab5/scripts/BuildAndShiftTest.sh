#!/bin/bash

if ! [ -d ../build/ ]; then
    echo 'No directory for build. Creating...'
    mkdir ../build
fi

cd ../build

cmake .. -Dkmp=ON -Dshift=ON -Dstest=ON
make

if ! [ -f "$Lab5_shifttest" ]; then
    echo "Build sucsessfull. Launching shift tests..."
    ./Lab5_shifttest
fi