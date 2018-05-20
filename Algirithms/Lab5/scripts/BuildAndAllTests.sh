#!/bin/bash

if ! [ -d ../build/ ]; then
    echo 'No directory for build. Creating...'
    mkdir ../build
fi

cd ../build

cmake .. -Dkmp=ON -Dshift=ON -Dtest=ON -Dstest=ON
make

if ! [ -f "$Lab5_test" ]; then
    echo "Build sucsessfull. Launching KMP tests..."
    ./Lab5_test
fi

if ! [ -f "$Lab5_shifttest" ]; then
    echo "Build sucsessfull. Launching Shift tests..."
    ./Lab5_shifttest
fi
