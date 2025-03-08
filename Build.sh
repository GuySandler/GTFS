#!/bin/bash

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
  mkdir build
fi

cd build
cmake ..
make