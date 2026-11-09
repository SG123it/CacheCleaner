#!/bin/bash

cd ..

mkdir  Output
cmake -B build -G "Unix Makefiles"
cmake --build build

cd dependencies/LINUX

tar -czvf ../../Output/LinuxArchive.tar.gz \
  -C . . \
  -C ../../build CacheCleaner


cd ..