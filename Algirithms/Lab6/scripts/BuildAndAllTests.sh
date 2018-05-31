#!/bin/bash

if ! [ -d ../build/ ]; then
    echo 'No directory for build. Creating...'
    mkdir ../build
fi

cd ../build

cmake .. -Dac=ON -Djo=ON -Dtest=ON -Djtest=ON
make

if ! [ -f "$Lab6_test" ]; then
    echo "Build sucsessfull. Launching AC tests..."
    ./Lab6_test
fi

if ! [ -f "$Lab6_jtest" ]; then
    echo "Build sucsessfull. Launching Joker tests..."
    ./Lab6_jtest
fi
