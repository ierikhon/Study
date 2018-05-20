#!/bin/bash

if ! [ -d ../build/ ]; then
    echo 'No directory for build. Creating...'
    mkdir ../build
fi

cd ../build

cmake .. -Dkmp=ON -Dshift=ON -Dtest=ON -Dstest=ON
echo 'Buld Completed Sucsessfully. Makefile is in ../build'