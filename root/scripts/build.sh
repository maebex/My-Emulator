#!/usr/bin/bash
cd ../..
if test -d ./build; then
  rm -r ./build
fi
mkdir build
cd build
cmake ..
make