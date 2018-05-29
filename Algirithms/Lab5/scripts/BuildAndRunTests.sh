#!/bin/bash

if ! [ -d ../build/ ]; then
    echo 'No directory for build. Creating...'
    mkdir ../build
fi

cd ../build

cmake .. -Dkmp=ON -Dshift=ON -Dtest=ON
make

if ! [ -f "$Lab5_test" ]; then
    echo "Build sucsessfull. Launching KMP tests..."
    ./Lab5_test
fi
